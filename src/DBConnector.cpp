#include "include/DBConnector.h"
#include <iostream>

DBConnector::DBConnector() : conn(nullptr), connected(false) {
    conn = mysql_init(nullptr);
    if (!conn) {
        std::cerr << "MySQL initialization failed" << std::endl;
    }
}

DBConnector::~DBConnector() {
    disconnect();
}

bool DBConnector::connect(const std::string& host, const std::string& user, 
                         const std::string& password, const std::string& db) {
    if (!conn) {
        std::cerr << "MySQL initialization failed" << std::endl;
        return false;
    }
    
    if (mysql_real_connect(conn, host.c_str(), user.c_str(), 
                         password.c_str(), db.c_str(), 0, nullptr, 0)) {
        connected = true;
        return true;
    }
    
    std::cerr << "MySQL connection error: " << mysql_error(conn) << std::endl;
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
        std::cerr << "Not connected to database" << std::endl;
        return false;
    }
    
    if (mysql_query(conn, query.c_str())) {
        std::cerr << "MySQL query error: " << mysql_error(conn) << std::endl;
        return false;
    }
    
    return true;
}

bool DBConnector::registerUser(const User& user) {
    std::string query = "INSERT INTO user_info (first_name, second_name, email, phone_number) VALUES ('" +
                       user.getName() + "', '', '" + user.getEmail() + "', '" + user.getPhone() + "')";
    
    return executeQuery(query);
}

bool DBConnector::authenticateUser(const std::string& email, const std::string& password) {
    // In a real application, you would check against hashed passwords
    // This is a simplified version for demonstration
    std::string query = "SELECT * FROM user_info WHERE email = '" + email + "'";
    
    if (!executeQuery(query)) {
        return false;
    }
    
    MYSQL_RES* result = mysql_store_result(conn);
    if (!result) {
        std::cerr << "Failed to get result: " << mysql_error(conn) << std::endl;
        return false;
    }
    
    // For now, we're just checking if the user exists
    bool userExists = (mysql_num_rows(result) > 0);
    mysql_free_result(result);
    
    // In a real implementation, you would check the password here
    // For demo purposes, just return true if the user exists
    return userExists;
}

std::vector<Location> DBConnector::loadCounties() {
    std::vector<Location> counties;
    
    std::string query = "SELECT town_id, town_name FROM town";
    
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
    
    // This query is just a placeholder as our schema doesn't actually have town-county relationships
    // In a real application, you would have proper relationships
    std::string query = "SELECT house_id, house_type FROM houses WHERE town_id = " + std::to_string(countyId);
    
    if (!executeQuery(query)) {
        return towns;
    }
    
    MYSQL_RES* result = mysql_store_result(conn);
    if (!result) {
        std::cerr << "Failed to get result: " << mysql_error(conn) << std::endl;
        return towns;
    }
    
    MYSQL_ROW row;
    int townCounter = 1;
    while ((row = mysql_fetch_row(result))) {
        int id = 100 * countyId + townCounter;
        std::string name = row[1];
        towns.push_back(Location(id, name, "town", countyId));
        townCounter++;
    }
    
    mysql_free_result(result);
    return towns;
}

std::vector<House> DBConnector::loadHouses(int townId) {
    std::vector<House> housesList;
    
    std::string query = "SELECT h.house_id, h.house_type, rc.deposit, rc.monthly_rent "
                       "FROM houses h "
                       "JOIN rental_cost rc ON h.house_id = rc.house_id AND h.town_id = rc.town_id "
                       "WHERE h.town_id = " + std::to_string(townId);
    
    if (!executeQuery(query)) {
        return housesList;
    }
    
    MYSQL_RES* result = mysql_store_result(conn);
    if (!result) {
        std::cerr << "Failed to get result: " << mysql_error(conn) << std::endl;
        return housesList;
    }
    
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        int id = std::stoi(row[0]);
        std::string type = row[1];
        double deposit = std::stod(row[2]);
        double rent = std::stod(row[3]);
        
        // Generate a generic address and map link
        std::string address = type + " in Town " + std::to_string(townId);
        std::string mapLink = "https://maps.google.com/?q=" + address;
        
        housesList.push_back(House(id, type, deposit, rent, townId, address, mapLink));
    }
    
    mysql_free_result(result);
    return housesList;
}

std::map<std::string, std::string> DBConnector::getPaymentDetails(int houseId, int townId) {
    std::map<std::string, std::string> details;
    
    std::string query = "SELECT bank_acount, m_pesa_till_no, owner_contacts "
                       "FROM payment_details "
                       "WHERE house_id = " + std::to_string(houseId) + 
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
