#include "include/MBomaHousingSystem.h"
#include "include/DBConnector.h"
#include "include/DBConfig.h"
#include <iostream>
#include <limits>
#include <iomanip>

MBomaHousingSystem::MBomaHousingSystem() : currentUserId(0), dbConnector(nullptr), isLoggedIn(false), useDatabase(false) {
    // Try to initialize database connection
    dbConnector = new DBConnector();
    if (dbConnector->connect(DBConfig::DB_HOST, DBConfig::DB_USER, DBConfig::DB_PASS, DBConfig::DB_NAME)) {
        useDatabase = true;
        std::cout << "Database connection established successfully.\n";
        // In a production system, we would load data from the database
        // For this implementation, we'll still use the sample data
    } else {
        std::cout << "Warning: Database connection failed. Using in-memory data.\n";
        std::cout << "Error: " << dbConnector->getLastError() << "\n";
        delete dbConnector;
        dbConnector = nullptr;
    }
    
    // Initialize sample data
    initializeData();
}

MBomaHousingSystem::~MBomaHousingSystem() {
    // Clean up database connection if it exists
    if (dbConnector) {
        dbConnector->disconnect();
        delete dbConnector;
        dbConnector = nullptr;
    }
}

void MBomaHousingSystem::initializeData() {
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

void MBomaHousingSystem::clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void MBomaHousingSystem::waitForEnter() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int MBomaHousingSystem::getNextId(const std::string& entityType) {
    if (entityType == "user") {
        return users.size() + 1;
    } else if (entityType == "booking") {
        return bookings.size() + 1;
    } else if (entityType == "payment") {
        return payments.size() + 1;
    }
    return 1;
}

void MBomaHousingSystem::displayCounties() {
    std::cout << "\n===== COUNTIES =====\n";
    for (const auto& location : locations) {
        if (location.getType() == "county") {
            std::cout << location.getId() << ". " << location.getName() << "\n";
        }
    }
}

void MBomaHousingSystem::displayTowns(int countyId) {
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

void MBomaHousingSystem::displayHouses(int townId) {
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

House* MBomaHousingSystem::findHouse(int houseId) {
    for (auto& house : houses) {
        if (house.getId() == houseId) {
            return &house;
        }
    }
    return nullptr;
}

User* MBomaHousingSystem::getCurrentUser() {
    if (!isLoggedIn || currentUserId <= 0 || currentUserId > users.size()) {
        return nullptr;
    }
    return &users[currentUserId - 1];
}

void MBomaHousingSystem::processPayment(int bookingId, double amount) {
    std::string paymentMethod;
    int choice;
    
    std::cout << "\n===== PAYMENT METHOD =====\n";
    std::cout << "1. M-Pesa\n";
    std::cout << "2. Bank Transfer\n";
    std::cout << "Enter your choice (1-2): ";
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    // Declare variables outside switch to avoid jump errors
    std::string phone;
    
    switch (choice) {
        case 1:
            paymentMethod = "M-Pesa";
            std::cout << "\nSimulating M-Pesa payment...\n";
            std::cout << "Enter your M-Pesa phone number: ";
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
    
    // Save payment to database if connected
    std::string receiptNumber = "";
    if (useDatabase && dbConnector && dbConnector->isConnected()) {
        receiptNumber = dbConnector->recordPayment(bookingId, amount, paymentMethod);
        if (!receiptNumber.empty()) {
            std::cout << "Payment saved to database.\n";
            // Update the receipt number if generated by database
            payment.setReceiptNumber(receiptNumber);
        } else {
            std::cout << "Warning: Failed to save payment to database. " << dbConnector->getLastError() << "\n";
        }
    }
    
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

void MBomaHousingSystem::searchHouses() {
    std::cout << "\n===== SEARCH HOUSES =====\n";
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    // Get search criteria from user
    std::string type = "";
    double minRent = 0.0;
    double maxRent = -1.0;
    int townId = -1;
    
    std::cout << "Enter house type (leave blank for any): ";
    std::getline(std::cin, type);
    
    std::cout << "Enter minimum monthly rent (0 for any): ";
    std::string minRentStr;
    std::getline(std::cin, minRentStr);
    if (!minRentStr.empty()) {
        try {
            minRent = std::stod(minRentStr);
        } catch (const std::exception& e) {
            std::cout << "Invalid input, using default (0).\n";
            minRent = 0.0;
        }
    }
    
    std::cout << "Enter maximum monthly rent (leave blank for any): ";
    std::string maxRentStr;
    std::getline(std::cin, maxRentStr);
    if (!maxRentStr.empty()) {
        try {
            maxRent = std::stod(maxRentStr);
        } catch (const std::exception& e) {
            std::cout << "Invalid input, using no maximum.\n";
            maxRent = -1.0;
        }
    }
    
    // Ask for location if desired
    std::cout << "Do you want to search in a specific town? (y/n): ";
    std::string searchByTown;
    std::getline(std::cin, searchByTown);
    
    if (searchByTown == "y" || searchByTown == "Y") {
        // Display counties first
        displayCounties();
        
        std::cout << "\nEnter county number: ";
        int countyId;
        std::cin >> countyId;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        // Display towns in the selected county
        displayTowns(countyId);
        
        std::cout << "\nEnter town number: ";
        std::cin >> townId;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    
    std::cout << "\nSearching for houses...\n";
    
    std::vector<House> searchResults;
    
    if (useDatabase && dbConnector && dbConnector->isConnected()) {
        // Use database search if available
        searchResults = dbConnector->searchHouses(type, minRent, maxRent, townId);
    } else {
        // Use in-memory search
        for (const auto& house : houses) {
            bool matches = true;
            
            // Check type
            if (!type.empty()) {
                if (house.getType().find(type) == std::string::npos) {
                    matches = false;
                }
            }
            
            // Check min rent
            if (minRent > 0 && house.getMonthlyRent() < minRent) {
                matches = false;
            }
            
            // Check max rent
            if (maxRent > 0 && house.getMonthlyRent() > maxRent) {
                matches = false;
            }
            
            // Check town
            if (townId > 0 && house.getLocationId() != townId) {
                matches = false;
            }
            
            if (matches && house.getAvailability()) {
                searchResults.push_back(house);
            }
        }
    }
    
    // Display search results
    displaySearchResults(searchResults);
}

void MBomaHousingSystem::displaySearchResults(const std::vector<House>& searchResults) {
    if (searchResults.empty()) {
        std::cout << "\nNo houses match your search criteria.\n";
    } else {
        std::cout << "\n===== SEARCH RESULTS (" << searchResults.size() << " houses found) =====\n";
        
        for (const auto& house : searchResults) {
            std::cout << "\nHouse ID: " << house.getId() << "\n";
            std::cout << "Type: " << house.getType() << "\n";
            std::cout << "Address: " << house.getAddress() << "\n";
            std::cout << "Deposit Fee: KES " << std::fixed << std::setprecision(2) << house.getDepositFee() << "\n";
            std::cout << "Monthly Rent: KES " << std::fixed << std::setprecision(2) << house.getMonthlyRent() << "\n";
            
            // Get town name
            std::string townName = "Unknown";
            for (const auto& location : locations) {
                if (location.getId() == house.getLocationId()) {
                    townName = location.getName();
                    break;
                }
            }
            
            std::cout << "Town: " << townName << "\n";
            std::cout << "Map Link: " << house.getMapLink() << "\n";
            std::cout << "Status: " << (house.getBookingStatus() ? "Booked until " + house.getBookedUntil() : "Available") << "\n";
            std::cout << "------------------------------\n";
        }
        
        std::cout << "\nWould you like to book one of these houses? (y/n): ";
        std::string bookHouse;
        std::getline(std::cin, bookHouse);
        
        if (bookHouse == "y" || bookHouse == "Y") {
            std::cout << "Enter the House ID you want to book: ";
            int houseId;
            std::cin >> houseId;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            // Find the house
            House* house = nullptr;
            for (auto& h : searchResults) {
                if (h.getId() == houseId) {
                    house = findHouse(houseId);
                    break;
                }
            }
            
            if (house && house->getAvailability() && !house->getBookingStatus()) {
                // Create booking in memory
                int bookingId = getNextId("booking");
                Booking booking(bookingId, currentUserId, houseId);
                bookings.push_back(booking);
                
                // Save booking to database if connected
                int dbBookingId = -1;
                if (useDatabase && dbConnector && dbConnector->isConnected()) {
                    int townId = house->getLocationId();
                    dbBookingId = dbConnector->createBooking(currentUserId, houseId, townId);
                    if (dbBookingId > 0) {
                        // Update the booking ID to match the database-generated ID
                        bookings.pop_back();  // Remove original booking
                        booking.setId(dbBookingId);  // Update ID
                        bookings.push_back(booking);  // Add updated booking
                        bookingId = dbBookingId;  // Update bookingId for further use
                        std::cout << "Booking saved to database.\n";
                    } else {
                        std::cout << "Warning: Failed to save booking to database. " << dbConnector->getLastError() << "\n";
                    }
                }
                
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
            } else if (house && house->getBookingStatus()) {
                std::cout << "This house is already booked until " << house->getBookedUntil() << ".\n";
            } else {
                std::cout << "Invalid house ID. Please try again.\n";
            }
        }
    }
    
    waitForEnter();
}

void MBomaHousingSystem::run() {
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
                        
                        // Save user to database
                        if (useDatabase && dbConnector && dbConnector->isConnected()) {
                            if (dbConnector->registerUser(newUser)) {
                                std::cout << "User info saved to database.\n";
                            } else {
                                std::cout << "Warning: Failed to save user to database. " << dbConnector->getLastError() << "\n";
                            }
                        }
                        
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
            std::cout << "2. Search Houses\n";
            std::cout << "3. View My Bookings\n";
            std::cout << "4. Logout\n";
            std::cout << "5. Exit\n";
            std::cout << "\nEnter your choice (1-5): ";
            
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
                                                        
                                                        // Save booking to database if connected
                                                        int dbBookingId = -1;
                                                        if (useDatabase && dbConnector && dbConnector->isConnected()) {
                                                            int townId = house->getLocationId();
                                                            dbBookingId = dbConnector->createBooking(currentUserId, houseId, townId);
                                                            if (dbBookingId > 0) {
                                                                // Update the booking ID to match the database-generated ID
                                                                bookings.pop_back();  // Remove original booking
                                                                booking.setId(dbBookingId);  // Update ID
                                                                bookings.push_back(booking);  // Add updated booking
                                                                bookingId = dbBookingId;  // Update bookingId for further use
                                                                std::cout << "Booking saved to database.\n";
                                                            } else {
                                                                std::cout << "Warning: Failed to save booking to database. " << dbConnector->getLastError() << "\n";
                                                            }
                                                        }
                                                        
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
                case 2:
                    // Search Houses
                    searchHouses();
                    break;
                case 3: {
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
                case 4:
                    // Logout
                    currentUserId = 0;
                    isLoggedIn = false;
                    std::cout << "Logged out successfully.\n";
                    waitForEnter();
                    break;
                case 5:
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
