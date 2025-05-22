#include "include/DBConnector.h"
#include "include/DBConfig.h"
#include "include/Utils.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <map>       // For std::map
#include <sstream>   // For std::stringstream
#include <iomanip>   // For std::put_time

DBConnector::DBConnector() : conn(nullptr), connected(false) {
    conn = mysql_init(nullptr);
    if (!conn) {
        std::cerr << "MySQL initialization failed" << std::endl;
    }
}

DBConnector::~DBConnector() {
    disconnect();
}

void DBConnector::setError(const std::string& error) {
    lastError = error;
    std::cerr << "DB Error: " << error << std::endl;
}

std::string DBConnector::getLastError() const {
    return lastError;
}

bool DBConnector::connect(const std::string& host, const std::string& user, 
                         const std::string& password, const std::string& db) {
    if (!conn) {
        setError("MySQL initialization failed");
        return false;
    }
    
    // Try to connect with retry logic
    for (int attempt = 0; attempt < DBConfig::CONNECTION_RETRY_ATTEMPTS; ++attempt) {
        if (mysql_real_connect(conn, host.c_str(), user.c_str(), 
                             password.c_str(), db.c_str(), 0, nullptr, 0)) {
            connected = true;
            return true;
        }
        
        // If not the last attempt, wait and retry
        if (attempt < DBConfig::CONNECTION_RETRY_ATTEMPTS - 1) {
            std::string errorMsg = "Connection attempt " + std::to_string(attempt + 1) + 
                                  " failed: " + mysql_error(conn) + 
                                  ". Retrying in " + 
                                  std::to_string(DBConfig::CONNECTION_RETRY_DELAY_MS / 1000.0) + 
                                  " seconds...";
            setError(errorMsg);
            
            // Sleep before retrying
            std::this_thread::sleep_for(
                std::chrono::milliseconds(DBConfig::CONNECTION_RETRY_DELAY_MS)
            );
        }
    }
    
    setError("Failed to connect to MySQL: " + std::string(mysql_error(conn)));
    return false;
}

void DBConnector::disconnect() {
    if (conn) {
        mysql_close(conn);
        conn = nullptr;
    }
    connected = false;
}

bool DBConnector::isConnected() const {
    return connected;
}

bool DBConnector::executeQuery(const std::string& query) {
    if (!connected) {
        setError("Not connected to database");
        return false;
    }
    
    if (mysql_query(conn, query.c_str())) {
        setError("MySQL query error: " + std::string(mysql_error(conn)));
        return false;
    }
    
    return true;
}

bool DBConnector::registerUser(const User& user) {
    // Escape strings to prevent SQL injection
    char* escapedName = new char[user.getName().length() * 2 + 1];
    char* escapedEmail = new char[user.getEmail().length() * 2 + 1];
    char* escapedPhone = new char[user.getPhone().length() * 2 + 1];
    char* escapedPassword = new char[user.getPassword().length() * 2 + 1];
    
    mysql_real_escape_string(conn, escapedName, user.getName().c_str(), user.getName().length());
    mysql_real_escape_string(conn, escapedEmail, user.getEmail().c_str(), user.getEmail().length());
    mysql_real_escape_string(conn, escapedPhone, user.getPhone().c_str(), user.getPhone().length());
    mysql_real_escape_string(conn, escapedPassword, user.getPassword().c_str(), user.getPassword().length());
    
    // Create the query with escaped values
    std::string query = "INSERT INTO user_info (first_name, second_name, email, phone_number, password) VALUES ('" + 
                       std::string(escapedName) + "', '', '" + 
                       std::string(escapedEmail) + "', '" + 
                       std::string(escapedPhone) + "', '" + 
                       std::string(escapedPassword) + "')";
    
    // Free allocated memory
    delete[] escapedName;
    delete[] escapedEmail;
    delete[] escapedPhone;
    delete[] escapedPassword;
    
    return executeQuery(query);
}

bool DBConnector::authenticateUser(const std::string& email, const std::string& password) {
    // Escape email to prevent SQL injection
    char* escapedEmail = new char[email.length() * 2 + 1];
    mysql_real_escape_string(conn, escapedEmail, email.c_str(), email.length());
    
    // Create query with escaped email - using LOWER function for case-insensitive comparison
    std::string query = "SELECT password FROM user_info WHERE LOWER(email) = LOWER('" + std::string(escapedEmail) + "')";
    
    // Free allocated memory
    delete[] escapedEmail;
    
    if (!executeQuery(query)) {
        return false;
    }
    
    MYSQL_RES* result = mysql_store_result(conn);
    if (!result) {
        std::cerr << "Failed to get result: " << mysql_error(conn) << std::endl;
        return false;
    }
    
    // Check if user exists and verify password
    if (mysql_num_rows(result) == 0) {
        mysql_free_result(result);
        return false;
    }
    
    MYSQL_ROW row = mysql_fetch_row(result);
    std::string hashedPassword = row[0] ? row[0] : "";
    mysql_free_result(result);
    
    // Verify the password
    return verifyPassword(password, hashedPassword);
}

std::vector<Location> DBConnector::loadCounties() {
    std::vector<Location> counties;
    
    std::string query = "SELECT county_id, county_name FROM county ORDER BY county_id";
    
    if (!executeQuery(query)) {
        return counties;
    }
    
    MYSQL_RES* result = mysql_store_result(conn);
    if (!result) {
        std::cerr << "Failed to get result: " << mysql_error(conn) << std::endl;
        return counties;
    }
    
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        int id = std::stoi(row[0]);
        std::string name = row[1];
        counties.push_back(Location(id, name, "county"));
    }
    
    mysql_free_result(result);
    return counties;
}

std::vector<Location> DBConnector::loadTowns(int countyId) {
    std::vector<Location> towns;
    
    std::string query = "SELECT town_id, town_name FROM town WHERE county_id = " + 
                        std::to_string(countyId) + " ORDER BY town_id";
    
    if (!executeQuery(query)) {
        return towns;
    }
    
    MYSQL_RES* result = mysql_store_result(conn);
    if (!result) {
        std::cerr << "Failed to get result: " << mysql_error(conn) << std::endl;
        return towns;
    }
    
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        int townId = std::stoi(row[0]);
        std::string name = row[1];
        towns.push_back(Location(townId, name, "town", countyId));
    }
    
    mysql_free_result(result);
    return towns;
}

std::vector<House> DBConnector::loadAllHouses() {
    std::vector<House> houses;
    
    std::string query = "SELECT h.house_id, h.house_type, h.town_id, "
                        "h.house_address, h.map_link, h.deposit_fee, h.monthly_rent, "
                        "h.is_available, h.is_booked, h.booked_until "
                        "FROM houses h ORDER BY h.town_id, h.house_id";
    
    if (!executeQuery(query)) {
        return houses;
    }
    
    MYSQL_RES* result = mysql_store_result(conn);
    if (!result) {
        std::cerr << "Failed to get result: " << mysql_error(conn) << std::endl;
        return houses;
    }
    
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        std::string id = row[0];
        std::string type = row[1];
        int townId = std::stoi(row[2]);
        std::string address = row[3] ? row[3] : "";
        std::string mapLink = row[4] ? row[4] : "";
        double deposit = row[5] ? std::stod(row[5]) : 0.0;
        double rent = row[6] ? std::stod(row[6]) : 0.0;
        bool isAvailable = row[7] ? (std::stoi(row[7]) == 1) : true;
        bool isBooked = row[8] ? (std::stoi(row[8]) == 1) : false;
        std::string bookedUntil = row[9] ? row[9] : "";
        
        House house(id, type, deposit, rent, townId, address, mapLink);
        house.setAvailability(isAvailable);
        
        if (isBooked && !bookedUntil.empty()) {
            house.book(bookedUntil);
        }
        
        houses.push_back(house);
    }
    
    mysql_free_result(result);
    return houses;
}

std::map<std::string, std::string> DBConnector::getPaymentDetails(const std::string& houseId, int townId) {
    std::map<std::string, std::string> details;
    
    std::string query = "SELECT bank_acount, m_pesa_till_no, owner_contacts "
                       "FROM payment_details "
                       "WHERE house_id = '" + houseId + "'" + 
                       " AND town_id = " + std::to_string(townId);
    
    if (!executeQuery(query)) {
        return details;
    }
    
    MYSQL_RES* result = mysql_store_result(conn);
    if (!result) {
        std::cerr << "Failed to get result: " << mysql_error(conn) << std::endl;
        return details;
    }
    
    MYSQL_ROW row;
    if ((row = mysql_fetch_row(result))) {
        details["bank_account"] = row[0];
        details["mpesa_till"] = row[1];
        details["owner_contacts"] = row[2];
    }
    
    mysql_free_result(result);
    return details;
}

std::vector<House> DBConnector::searchHouses(const std::string& type, 
                                           double minRent, 
                                           double maxRent, 
                                           int townId) {
    std::vector<House> results;
    
    // Build the query based on search criteria
    std::stringstream queryStream;
    queryStream << "SELECT h.house_id, h.house_type, rc.deposit, rc.monthly_rent, h.town_id, "
                << "CONCAT(t.town_name, ' Area, House #', h.house_id) as address, "
                << "CONCAT('https://maps.google.com/?q=', t.town_name) as map_link "
                << "FROM houses h "
                << "JOIN rental_cost rc ON h.house_id = rc.house_id AND h.town_id = rc.town_id "
                << "JOIN town t ON h.town_id = t.town_id "
                << "WHERE 1=1 ";  // This allows us to conditionally add clauses
    
    // Add type condition if provided
    if (!type.empty()) {
        queryStream << "AND h.house_type LIKE '%" << type << "%' ";
    }
    
    // Add minimum rent condition if provided
    if (minRent > 0) {
        queryStream << "AND rc.monthly_rent >= " << minRent << " ";
    }
    
    // Add maximum rent condition if provided
    if (maxRent > 0) {
        queryStream << "AND rc.monthly_rent <= " << maxRent << " ";
    }
    
    // Add town condition if provided
    if (townId > 0) {
        queryStream << "AND h.town_id = " << townId << " ";
    }
    
    // Execute the query
    std::string query = queryStream.str();
    if (!executeQuery(query)) {
        return results;
    }
    
    // Process results
    MYSQL_RES* result = mysql_store_result(conn);
    if (!result) {
        std::cerr << "Failed to get result: " << mysql_error(conn) << std::endl;
        return results;
    }
    
    // Extract houses from the result
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        std::string id = row[0];
        std::string houseType = row[1];
        double deposit = std::stod(row[2]);
        double monthlyRent = std::stod(row[3]);
        int houseLocationId = std::stoi(row[4]);
        std::string address = row[5];
        std::string mapLink = row[6];
        
        // Create a house object and add to results
        results.push_back(House(id, houseType, deposit, monthlyRent, 
                              houseLocationId, address, mapLink));
    }
    
    mysql_free_result(result);
    return results;
}

std::vector<Booking> DBConnector::loadBookings(int userId) {
    std::vector<Booking> bookings;
    
    if (!isConnected()) {
        setError("Not connected to database");
        return bookings;
    }
    
    std::string query = "SELECT booking_id, user_id, house_id, booking_date, expiry_date, is_paid FROM bookings";
    
    // If userId is provided, filter bookings for this user only
    if (userId > 0) {
        query += " WHERE user_id = " + std::to_string(userId);
    }
    
    if (mysql_query(conn, query.c_str())) {
        setError(mysql_error(conn));
        return bookings;
    }
    
    MYSQL_RES* result = mysql_store_result(conn);
    if (!result) {
        setError(mysql_error(conn));
        return bookings;
    }
    
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        int bookingId = std::stoi(row[0]);
        int userIdFromDb = std::stoi(row[1]);
        std::string houseId = row[2];
        
        // Create booking object with core data
        Booking booking(bookingId, userIdFromDb, houseId);
        
        // Set dates from database
        if (row[3]) booking.setBookingDate(row[3]);
        if (row[4]) booking.setExpiryDate(row[4]);
        
        // Set payment status if booking is paid
        if (row[5] && std::string(row[5]) == "1") {
            booking.markAsPaid();
        }
        
        bookings.push_back(booking);
    }
    
    mysql_free_result(result);
    return bookings;
}

int DBConnector::createBooking(int userId, const std::string& houseId, int townId) {
    // Get the current date and expiry date
    std::string bookingDate = getCurrentDateTime();
    
    // Calculate expiry date (30 days from now)
    auto now = std::chrono::system_clock::now();
    auto expiry = now + std::chrono::hours(24 * 30);
    std::time_t expiry_time = std::chrono::system_clock::to_time_t(expiry);
    
    std::stringstream ss;
    ss << std::put_time(std::localtime(&expiry_time), "%Y-%m-%d %H:%M:%S");
    std::string expiryDate = ss.str();
    
    // Create the booking query
    std::string query = "INSERT INTO bookings (user_id, house_id, town_id, booking_date, expiry_date, is_paid) "
                        "VALUES (" + std::to_string(userId) + ", '" + 
                        houseId + "', " + 
                        std::to_string(townId) + ", '" + 
                        bookingDate + "', '" + 
                        expiryDate + "', 0)";
                        
    if (!executeQuery(query)) {
        return -1;
    }
    
    // Get the auto-generated booking ID
    unsigned long bookingId = mysql_insert_id(conn);
    
    // Mark the house as booked
    std::string updateHouseQuery = "UPDATE houses SET is_booked = 1 WHERE house_id = '" + 
                                  houseId + "' AND town_id = " + 
                                  std::to_string(townId);
    executeQuery(updateHouseQuery);
    
    return static_cast<int>(bookingId);
}

std::string DBConnector::recordPayment(int bookingId, double amount, const std::string& paymentMethod) {
    std::string paymentDate = getCurrentDateTime();
    std::string receiptNumber = generateReceiptNumber();
    
    // Escape strings to prevent SQL injection
    char* escapedMethod = new char[paymentMethod.length() * 2 + 1];
    char* escapedReceipt = new char[receiptNumber.length() * 2 + 1];
    
    mysql_real_escape_string(conn, escapedMethod, paymentMethod.c_str(), paymentMethod.length());
    mysql_real_escape_string(conn, escapedReceipt, receiptNumber.c_str(), receiptNumber.length());
    
    // Create the payment query
    std::string query = "INSERT INTO payments (booking_id, amount, payment_date, payment_method, receipt_number) "
                        "VALUES (" + std::to_string(bookingId) + ", " + 
                        std::to_string(amount) + ", '" + 
                        paymentDate + "', '" + 
                        std::string(escapedMethod) + "', '" + 
                        std::string(escapedReceipt) + "')";
                        
    // Free allocated memory
    delete[] escapedMethod;
    delete[] escapedReceipt;
    
    if (!executeQuery(query)) {
        return "";
    }
    
    // Mark the booking as paid
    std::string updateBookingQuery = "UPDATE bookings SET is_paid = 1 WHERE booking_id = " + 
                                    std::to_string(bookingId);
    executeQuery(updateBookingQuery);
    
    return receiptNumber;
}

std::vector<User> DBConnector::loadUsers() {
    std::vector<User> users;
    
    std::string query = "SELECT user_id, first_name, phone_number, email, password FROM user_info";
    
    if (!executeQuery(query)) {
        return users;
    }
    
    MYSQL_RES* result = mysql_store_result(conn);
    if (!result) {
        std::cerr << "Failed to get result: " << mysql_error(conn) << std::endl;
        return users;
    }
    
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        // Extract user data
        // user_id is in row[0] but we don't need it currently
        std::string name = row[1] ? row[1] : "";
        std::string phone = row[2] ? row[2] : "";
        std::string email = row[3] ? row[3] : "";
        std::string hashedPassword = row[4] ? row[4] : "";
        
        // Create user with the existing hashed password (not re-hashing)
        User user;
        user.setName(name);
        user.setPhone(phone);
        user.setEmail(email);
        user.setPasswordHash(hashedPassword); // Direct set of hashed password
        users.push_back(user);
    }
    
    mysql_free_result(result);
    return users;
}

std::vector<Location> DBConnector::loadAllTowns() {
    std::vector<Location> towns;
    
    std::string query = "SELECT t.town_id, t.town_name, t.county_id FROM town t ORDER BY t.town_id";
    
    if (!executeQuery(query)) {
        return towns;
    }
    
    MYSQL_RES* result = mysql_store_result(conn);
    if (!result) {
        std::cerr << "Failed to get result: " << mysql_error(conn) << std::endl;
        return towns;
    }
    
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        int townId = std::stoi(row[0]);
        std::string name = row[1];
        int countyId = std::stoi(row[2]);
        towns.push_back(Location(townId, name, "town", countyId));
    }
    
    mysql_free_result(result);
    return towns;
}
