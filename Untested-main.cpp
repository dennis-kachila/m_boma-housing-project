#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <chrono>
#include <algorithm>
#include <limits>

// Forward declarations
class User;
class House;
class Location;
class Booking;
class Payment;

// Utility functions
std::string getCurrentDateTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    
    std::stringstream ss;
    ss << std::put_time(std::localtime(&now_time), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

std::string generateReceiptNumber() {
    static int receiptCounter = 1000;
    receiptCounter++;
    
    std::stringstream ss;
    ss << "RCP" << receiptCounter;
    return ss.str();
}

// User class to handle registration and authentication
class User {
private:
    std::string name;
    std::string phone;
    std::string email;
    std::string password;
    bool isLoggedIn;

public:
    User() : isLoggedIn(false) {}
    
    User(const std::string& name, const std::string& phone, 
         const std::string& email, const std::string& password)
        : name(name), phone(phone), email(email), password(password), isLoggedIn(false) {}
    
    bool registerUser() {
        std::cout << "\n===== USER REGISTRATION =====\n";
        
        std::cout << "Enter your name: ";
        std::getline(std::cin, name);
        
        std::cout << "Enter your phone number: ";
        std::getline(std::cin, phone);
        
        std::cout << "Enter your email: ";
        std::getline(std::cin, email);
        
        std::cout << "Enter your password: ";
        std::getline(std::cin, password);
        
        std::cout << "\nRegistration successful!\n";
        return true;
    }
    
    bool login(const std::string& inputEmail, const std::string& inputPassword) {
        if (email == inputEmail && password == inputPassword) {
            isLoggedIn = true;
            return true;
        }
        return false;
    }
    
    void logout() {
        isLoggedIn = false;
    }
    
    bool isAuthenticated() const {
        return isLoggedIn;
    }
    
    std::string getName() const {
        return name;
    }
    
    std::string getEmail() const {
        return email;
    }
    
    std::string getPhone() const {
        return phone;
    }
};

// Location class to represent counties and towns
class Location {
private:
    int id;
    std::string name;
    std::string type; // "county" or "town"
    int parentId;     // For towns, this is the county ID

public:
    Location(int id, const std::string& name, const std::string& type, int parentId = -1)
        : id(id), name(name), type(type), parentId(parentId) {}
    
    int getId() const {
        return id;
    }
    
    std::string getName() const {
        return name;
    }
    
    std::string getType() const {
        return type;
    }
    
    int getParentId() const {
        return parentId;
    }
};

// House class to represent available houses
class House {
private:
    int id;
    std::string type;        // e.g., "Apartment", "Bungalow", etc.
    double depositFee;
    double monthlyRent;
    int locationId;          // Town ID
    std::string address;
    std::string mapLink;
    bool isAvailable;
    bool isBooked;
    std::string bookedUntil;

public:
    House(int id, const std::string& type, double depositFee, double monthlyRent,
          int locationId, const std::string& address, const std::string& mapLink)
        : id(id), type(type), depositFee(depositFee), monthlyRent(monthlyRent),
          locationId(locationId), address(address), mapLink(mapLink),
          isAvailable(true), isBooked(false), bookedUntil("") {}
    
    int getId() const {
        return id;
    }
    
    std::string getType() const {
        return type;
    }
    
    double getDepositFee() const {
        return depositFee;
    }
    
    double getMonthlyRent() const {
        return monthlyRent;
    }
    
    int getLocationId() const {
        return locationId;
    }
    
    std::string getAddress() const {
        return address;
    }
    
    std::string getMapLink() const {
        return mapLink;
    }
    
    bool getAvailability() const {
        return isAvailable;
    }
    
    bool getBookingStatus() const {
        return isBooked;
    }
    
    std::string getBookedUntil() const {
        return bookedUntil;
    }
    
    void setAvailability(bool available) {
        isAvailable = available;
    }
    
    void book(const std::string& until) {
        isBooked = true;
        bookedUntil = until;
    }
    
    void unbook() {
        isBooked = false;
        bookedUntil = "";
    }
};

// Booking class to handle house reservations
class Booking {
private:
    int id;
    int userId;
    int houseId;
    std::string bookingDate;
    std::string expiryDate;
    bool isPaid;

public:
    Booking(int id, int userId, int houseId)
        : id(id), userId(userId), houseId(houseId), isPaid(false) {
        
        bookingDate = getCurrentDateTime();
        
        // Calculate expiry date (30 days from now)
        auto now = std::chrono::system_clock::now();
        auto expiry = now + std::chrono::hours(24 * 30);
        std::time_t expiry_time = std::chrono::system_clock::to_time_t(expiry);
        
        std::stringstream ss;
        ss << std::put_time(std::localtime(&expiry_time), "%Y-%m-%d %H:%M:%S");
        expiryDate = ss.str();
    }
    
    int getId() const {
        return id;
    }
    
    int getUserId() const {
        return userId;
    }
    
    int getHouseId() const {
        return houseId;
    }
    
    std::string getBookingDate() const {
        return bookingDate;
    }
    
    std::string getExpiryDate() const {
        return expiryDate;
    }
    
    bool getPaymentStatus() const {
        return isPaid;
    }
    
    void markAsPaid() {
        isPaid = true;
    }
};

// Payment class to handle transactions
class Payment {
private:
    int id;
    int bookingId;
    double amount;
    std::string paymentDate;
    std::string paymentMethod;
    std::string receiptNumber;

public:
    Payment(int id, int bookingId, double amount, const std::string& paymentMethod)
        : id(id), bookingId(bookingId), amount(amount), paymentMethod(paymentMethod) {
        
        paymentDate = getCurrentDateTime();
        receiptNumber = generateReceiptNumber();
    }
    
    void generateReceipt(const User& user, const House& house) const {
        std::cout << "\n========== PAYMENT RECEIPT ==========\n";
        std::cout << "Receipt Number: " << receiptNumber << "\n";
        std::cout << "Date: " << paymentDate << "\n";
        std::cout << "Customer: " << user.getName() << "\n";
        std::cout << "Phone: " << user.getPhone() << "\n";
        std::cout << "Email: " << user.getEmail() << "\n";
        std::cout << "Property: " << house.getType() << " at " << house.getAddress() << "\n";
        std::cout << "Amount Paid: KES " << std::fixed << std::setprecision(2) << amount << "\n";
        std::cout << "Payment Method: " << paymentMethod << "\n";
        std::cout << "Status: PAID\n";
        std::cout << "======================================\n";
        
        // Save receipt to file
        std::ofstream receiptFile(receiptNumber + ".txt");
        if (receiptFile.is_open()) {
            receiptFile << "========== PAYMENT RECEIPT ==========\n";
            receiptFile << "Receipt Number: " << receiptNumber << "\n";
            receiptFile << "Date: " << paymentDate << "\n";
            receiptFile << "Customer: " << user.getName() << "\n";
            receiptFile << "Phone: " << user.getPhone() << "\n";
            receiptFile << "Email: " << user.getEmail() << "\n";
            receiptFile << "Property: " << house.getType() << " at " << house.getAddress() << "\n";
            receiptFile << "Amount Paid: KES " << std::fixed << std::setprecision(2) << amount << "\n";
            receiptFile << "Payment Method: " << paymentMethod << "\n";
            receiptFile << "Status: PAID\n";
            receiptFile << "======================================\n";
            receiptFile.close();
            std::cout << "Receipt saved to " << receiptNumber << ".txt\n";
        }
    }
};

// Housing Management System class
class MBomaHousingSystem {
private:
    std::vector<User> users;
    std::vector<Location> locations;
    std::vector<House> houses;
    std::vector<Booking> bookings;
    std::vector<Payment> payments;
    
    int currentUserId;
    bool isLoggedIn;
    
    // Initialize sample data
    void initializeData() {
        // Add counties
        locations.push_back(Location(1, "Nairobi", "county"));
        locations.push_back(Location(2, "Mombasa", "county"));
        locations.push_back(Location(3, "Kisumu", "county"));
        locations.push_back(Location(4, "Nakuru", "county"));
        
        // Add towns in Nairobi
        locations.push_back(Location(101, "Karen", "town", 1));
        locations.push_back(Location(102, "Kitengela", "town", 1));
        locations.push_back(Location(103, "Runda", "town", 1));
        locations.push_back(Location(104, "Westlands", "town", 1));
        
        // Add towns in Mombasa
        locations.push_back(Location(201, "Nyali", "town", 2));
        locations.push_back(Location(202, "Bamburi", "town", 2));
        
        // Add towns in Kisumu
        locations.push_back(Location(301, "Milimani", "town", 3));
        
        // Add towns in Nakuru
        locations.push_back(Location(401, "Bahati", "town", 4));
        
        // Add houses in Karen (Nairobi)
        houses.push_back(House(1, "Bungalow", 100000, 50000, 101, "Karen Road, House #123", "https://maps.google.com/?q=Karen,Nairobi"));
        houses.push_back(House(2, "Villa", 150000, 75000, 101, "Karen Drive, House #456", "https://maps.google.com/?q=Karen,Nairobi"));
        
        // Add houses in Kitengela (Nairobi)
        houses.push_back(House(3, "Apartment", 30000, 15000, 102, "Kitengela Plaza, Apt #10", "https://maps.google.com/?q=Kitengela,Nairobi"));
        houses.push_back(House(4, "Studio", 20000, 10000, 102, "Kitengela Heights, Apt #5", "https://maps.google.com/?q=Kitengela,Nairobi"));
        
        // Add houses in Runda (Nairobi)
        houses.push_back(House(5, "Mansion", 200000, 100000, 103, "Runda Estate, House #789", "https://maps.google.com/?q=Runda,Nairobi"));
        
        // Add houses in Westlands (Nairobi)
        houses.push_back(House(6, "Penthouse", 120000, 60000, 104, "Westlands Towers, Apt #20", "https://maps.google.com/?q=Westlands,Nairobi"));
        
        // Add houses in Nyali (Mombasa)
        houses.push_back(House(7, "Beach House", 180000, 90000, 201, "Nyali Beach Road, House #101", "https://maps.google.com/?q=Nyali,Mombasa"));
        
        // Add houses in Bamburi (Mombasa)
        houses.push_back(House(8, "Cottage", 40000, 20000, 202, "Bamburi Beach, House #202", "https://maps.google.com/?q=Bamburi,Mombasa"));
        
        // Add houses in Milimani (Kisumu)
        houses.push_back(House(9, "Townhouse", 60000, 30000, 301, "Milimani Estate, House #303", "https://maps.google.com/?q=Milimani,Kisumu"));
        
        // Add houses in Bahati (Nakuru)
        houses.push_back(House(10, "Duplex", 50000, 25000, 401, "Bahati Heights, House #404", "https://maps.google.com/?q=Bahati,Nakuru"));
        
        // Add a test user
        users.push_back(User("Test User", "0712345678", "test@example.com", "password"));
    }
    
    void clearScreen() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }
    
    void waitForEnter() {
        std::cout << "\nPress Enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    
    int getNextId(const std::string& entityType) {
        if (entityType == "user") {
            return users.size() + 1;
        } else if (entityType == "booking") {
            return bookings.size() + 1;
        } else if (entityType == "payment") {
            return payments.size() + 1;
        }
        return 1;
    }
    
    void displayCounties() {
        std::cout << "\n===== COUNTIES =====\n";
        for (const auto& location : locations) {
            if (location.getType() == "county") {
                std::cout << location.getId() << ". " << location.getName() << "\n";
            }
        }
    }
    
    void displayTowns(int countyId) {
        std::cout << "\n===== TOWNS IN ";
        
        // Find county name
        for (const auto& location : locations) {
            if (location.getType() == "county" && location.getId() == countyId) {
                std::cout << location.getName() << " =====\n";
                break;
            }
        }
        
        bool found = false;
        for (const auto& location : locations) {
            if (location.getType() == "town" && location.getParentId() == countyId) {
                std::cout << location.getId() << ". " << location.getName() << "\n";
                found = true;
            }
        }
        
        if (!found) {
            std::cout << "No towns available in this county.\n";
        }
    }
    
    void displayHouses(int townId) {
        std::cout << "\n===== HOUSES IN ";
        
        // Find town name
        for (const auto& location : locations) {
            if (location.getType() == "town" && location.getId() == townId) {
                std::cout << location.getName() << " =====\n";
                break;
            }
        }
        
        bool found = false;
        for (const auto& house : houses) {
            if (house.getLocationId() == townId && house.getAvailability()) {
                std::cout << "\nHouse ID: " << house.getId() << "\n";
                std::cout << "Type: " << house.getType() << "\n";
                std::cout << "Address: " << house.getAddress() << "\n";
                std::cout << "Deposit Fee: KES " << std::fixed << std::setprecision(2) << house.getDepositFee() << "\n";
                std::cout << "Monthly Rent: KES " << std::fixed << std::setprecision(2) << house.getMonthlyRent() << "\n";
                std::cout << "Map Link: " << house.getMapLink() << "\n";
                std::cout << "Status: " << (house.getBookingStatus() ? "Booked until " + house.getBookedUntil() : "Available") << "\n";
                std::cout << "------------------------------\n";
                found = true;
            }
        }
        
        if (!found) {
            std::cout << "No houses available in this town.\n";
        }
    }
    
    House* findHouse(int houseId) {
        for (auto& house : houses) {
            if (house.getId() == houseId) {
                return &house;
            }
        }
        return nullptr;
    }
    
    User* getCurrentUser() {
        if (!isLoggedIn || currentUserId <= 0 || currentUserId > users.size()) {
            return nullptr;
        }
        return &users[currentUserId - 1];
    }
    
    void processPayment(int bookingId, double amount) {
        std::string paymentMethod;
        int choice;
        
        std::cout << "\n===== PAYMENT METHOD =====\n";
        std::cout << "1. M-Pesa\n";
        std::cout << "2. Bank Transfer\n";
        std::cout << "Enter your choice (1-2): ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        switch (choice) {
            case 1:
                paymentMethod = "M-Pesa";
                std::cout << "\nSimulating M-Pesa payment...\n";
                std::cout << "Enter your M-Pesa phone number: ";
                std::string phone;
                std::getline(std::cin, phone);
                std::cout << "Enter M-Pesa PIN: ****\n";
                std::cout << "Payment processing...\n";
                break;
            case 2:
                paymentMethod = "Bank Transfer";
                std::cout << "\nBank Transfer Details:\n";
                std::cout << "Bank: M-Boma Bank\n";
                std::cout << "Account Number: 1234567890\n";
                std::cout << "Amount: KES " << std::fixed << std::setprecision(2) << amount << "\n";
                std::cout << "Reference: MBOMA" << bookingId << "\n";
                std::cout << "\nSimulating bank transfer...\n";
                break;
            default:
                std::cout << "Invalid choice. Defaulting to M-Pesa.\n";
                paymentMethod = "M-Pesa";
                break;
        }
        
        // Create payment record
        int paymentId = getNextId("payment");
        Payment payment(paymentId, bookingId, amount, paymentMethod);
        payments.push_back(payment);
        
        // Find the booking and mark it as paid
        for (auto& booking : bookings) {
            if (booking.getId() == bookingId) {
                booking.markAsPaid();
                
                // Find the house and update its status
                House* house = findHouse(booking.getHouseId());
                if (house) {
                    house->setAvailability(false);
                    
                    // Generate receipt
                    User* user = getCurrentUser();
                    if (user) {
                        payment.generateReceipt(*user, *house);
                    }
                }
                break;
            }
        }
        
        std::cout << "Payment successful!\n";
    }

public:
    MBomaHousingSystem() : currentUserId(0), isLoggedIn(false) {
        initializeData();
    }
    
    void run() {
        bool running = true;
        
        while (running) {
            clearScreen();
            std::cout << "======================================\n";
            std::cout << "   M-BOMA HOUSING MANAGEMENT SYSTEM   \n";
            std::cout << "======================================\n";
            
            if (!isLoggedIn) {
                std::cout << "\n1. Register\n";
                std::cout << "2. Login\n";
                std::cout << "3. Exit\n";
                std::cout << "\nEnter your choice (1-3): ";
                
                int choice;
                std::cin >> choice;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                
                switch (choice) {
                    case 1: {
                        User newUser;
                        if (newUser.registerUser()) {
                            users.push_back(newUser);
                            currentUserId = users.size();
                            isLoggedIn = true;
                            std::cout << "You are now logged in!\n";
                            waitForEnter();
                        }
                        break;
                    }
                    case 2: {
                        std::string email, password;
                        std::cout << "\n===== LOGIN =====\n";
                        std::cout << "Email: ";
                        std::getline(std::cin, email);
                        std::cout << "Password: ";
                        std::getline(std::cin, password);
                        
                        bool loginSuccess = false;
                        for (size_t i = 0; i < users.size(); ++i) {
                            if (users[i].login(email, password)) {
                                currentUserId = i + 1;
                                isLoggedIn = true;
                                loginSuccess = true;
                                std::cout << "Login successful!\n";
                                waitForEnter();
                                break;
                            }
                        }
                        
                        if (!loginSuccess) {
                            std::cout << "Invalid email or password. Please try again.\n";
                            waitForEnter();
                        }
                        break;
                    }
                    case 3:
                        running = false;
                        break;
                    default:
                        std::cout << "Invalid choice. Please try again.\n";
                        waitForEnter();
                        break;
                }
            } else {
                // User is logged in
                User* currentUser = getCurrentUser();
                std::cout << "\nWelcome, " << currentUser->getName() << "!\n";
                
                std::cout << "\n1. Browse Counties\n";
                std::cout << "2. View My Bookings\n";
                std::cout << "3. Logout\n";
                std::cout << "4. Exit\n";
                std::cout << "\nEnter your choice (1-4): ";
                
                int choice;
                std::cin >> choice;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                
                switch (choice) {
                    case 1: {
                        // Browse counties
                        bool browsing = true;
                        while (browsing) {
                            displayCounties();
                            std::cout << "\n0. Back to Main Menu\n";
                            std::cout << "Enter county number (or 0 to go back): ";
                            
                            int countyId;
                            std::cin >> countyId;
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            
                            if (countyId == 0) {
                                browsing = false;
                            } else {
                                // Display towns in the selected county
                                bool validCounty = false;
                                for (const auto& location : locations) {
                                    if (location.getType() == "county" && location.getId() == countyId) {
                                        validCounty = true;
                                        break;
                                    }
                                }
                                
                                if (validCounty) {
                                    bool browsingTowns = true;
                                    while (browsingTowns) {
                                        displayTowns(countyId);
                                        std::cout << "\n0. Back to Counties\n";
                                        std::cout << "Enter town number (or 0 to go back): ";
                                        
                                        int townId;
                                        std::cin >> townId;
                                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                        
                                        if (townId == 0) {
                                            browsingTowns = false;
                                        } else {
                                            // Display houses in the selected town
                                            bool validTown = false;
                                            for (const auto& location : locations) {
                                                if (location.getType() == "town" && location.getId() == townId) {
                                                    validTown = true;
                                                    break;
                                                }
                                            }
                                            
                                            if (validTown) {
                                                bool browsingHouses = true;
                                                while (browsingHouses) {
                                                    displayHouses(townId);
                                                    std::cout << "\n0. Back to Towns\n";
                                                    std::cout << "Enter house ID to book (or 0 to go back): ";
                                                    
                                                    int houseId;
                                                    std::cin >> houseId;
                                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                                    
                                                    if (houseId == 0) {
                                                        browsingHouses = false;
                                                    } else {
                                                        // Book the selected house
                                                        House* house = findHouse(houseId);
                                                        if (house && house->getAvailability() && !house->getBookingStatus()) {
                                                            // Create booking
                                                            int bookingId = getNextId("booking");
                                                            Booking booking(bookingId, currentUserId, houseId);
                                                            bookings.push_back(booking);
                                                            
                                                            // Mark house as booked
                                                            house->book(booking.getExpiryDate());
                                                            
                                                            std::cout << "\nHouse booked successfully!\n";
                                                            std::cout << "Booking ID: " << bookingId << "\n";
                                                            std::cout << "Booking Date: " << booking.getBookingDate() << "\n";
                                                            std::cout << "Expiry Date: " << booking.getExpiryDate() << "\n";
                                                            
                                                            // Ask for payment
                                                            std::cout << "\nWould you like to make a payment now? (y/n): ";
                                                            char payNow;
                                                            std::cin >> payNow;
                                                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                                            
                                                            if (payNow == 'y' || payNow == 'Y') {
                                                                processPayment(bookingId, house->getDepositFee());
                                                            } else {
                                                                std::cout << "You can make the payment later from the 'View My Bookings' menu.\n";
                                                            }
                                                            
                                                            waitForEnter();
                                                            browsingHouses = false;
                                                            browsingTowns = false;
                                                            browsing = false;
                                                        } else if (house && house->getBookingStatus()) {
                                                            std::cout << "This house is already booked until " << house->getBookedUntil() << ".\n";
                                                            waitForEnter();
                                                        } else {
                                                            std::cout << "Invalid house ID. Please try again.\n";
                                                            waitForEnter();
                                                        }
                                                    }
                                                }
                                            } else {
                                                std::cout << "Invalid town ID. Please try again.\n";
                                                waitForEnter();
                                            }
                                        }
                                    }
                                } else {
                                    std::cout << "Invalid county ID. Please try again.\n";
                                    waitForEnter();
                                }
                            }
                        }
                        break;
                    }
                    case 2: {
                        // View My Bookings
                        std::cout << "\n===== MY BOOKINGS =====\n";
                        bool hasBookings = false;
                        
                        for (const auto& booking : bookings) {
                            if (booking.getUserId() == currentUserId) {
                                hasBookings = true;
                                House* house = findHouse(booking.getHouseId());
                                
                                if (house) {
                                    std::cout << "\nBooking ID: " << booking.getId() << "\n";
                                    std::cout << "House: " << house->getType() << " at " << house->getAddress() << "\n";
                                    std::cout << "Booking Date: " << booking.getBookingDate() << "\n";
                                    std::cout << "Expiry Date: " << booking.getExpiryDate() << "\n";
                                    std::cout << "Payment Status: " << (booking.getPaymentStatus() ? "Paid" : "Pending") << "\n";
                                    std::cout << "------------------------------\n";
                                    
                                    if (!booking.getPaymentStatus()) {
                                        std::cout << "Would you like to make a payment for this booking? (y/n): ";
                                        char payNow;
                                        std::cin >> payNow;
                                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                        
                                        if (payNow == 'y' || payNow == 'Y') {
                                            processPayment(booking.getId(), house->getDepositFee());
                                        }
                                    }
                                }
                            }
                        }
                        
                        if (!hasBookings) {
                            std::cout << "You have no bookings yet.\n";
                        }
                        
                        waitForEnter();
                        break;
                    }
                    case 3:
                        // Logout
                        currentUserId = 0;
                        isLoggedIn = false;
                        std::cout << "Logged out successfully.\n";
                        waitForEnter();
                        break;
                    case 4:
                        // Exit
                        running = false;
                        break;
                    default:
                        std::cout << "Invalid choice. Please try again.\n";
                        waitForEnter();
                        break;
                }
            }
        }
        
        std::cout << "\nThank you for using M-Boma Housing Management System!\n";
    }
};

int main() {
    MBomaHousingSystem system;
    system.run();
    return 0;
}
