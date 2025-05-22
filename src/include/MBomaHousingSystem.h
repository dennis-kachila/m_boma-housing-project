#ifndef MBOMA_HOUSING_SYSTEM_H
#define MBOMA_HOUSING_SYSTEM_H

#include <vector>
#include <string>
#include <map>
#include "User.h"
#include "Location.h"
#include "House.h"
#include "Booking.h"
#include "Payment.h"

// Forward declaration for DBConnector
class DBConnector;

/**
 * @brief Main housing management system class
 */
class MBomaHousingSystem {
private:
    std::vector<User> users;
    std::vector<Location> locations;
    std::vector<House> houses;
    std::vector<Booking> bookings;
    std::vector<Payment> payments;
    
    DBConnector* dbConnector;
    bool useDatabase;
    
    int currentUserId;
    bool isLoggedIn;
    
    /**
     * @brief Initialize sample data
     */
    void initializeData();
    
    /**
     * @brief Clear console screen (cross-platform)
     */
    void clearScreen();
    
    /**
     * @brief Wait for user to press Enter
     */
    void waitForEnter();
    
    /**
     * @brief Get next available ID for a given entity type
     * @param entityType Type of entity ("user", "booking", or "payment")
     * @return Next available ID
     */
    int getNextId(const std::string& entityType);
    
    /**
     * @brief Display list of counties
     */
    void displayCounties();
    
    /**
     * @brief Display towns in a specific county
     * @param countyId County ID
     */
    void displayTowns(int countyId);
    
    /**
     * @brief Display houses in a specific town
     * @param townId Town ID
     */
    void displayHouses(int townId);
    
    /**
     * @brief Find a house by ID
     * @param houseId House ID to find
     * @return Pointer to house if found, nullptr otherwise
     */
    House* findHouse(const std::string& houseId);
    
    /**
     * @brief Get current logged-in user
     * @return Pointer to current user if logged in, nullptr otherwise
     */
    User* getCurrentUser();
    
    /**
     * @brief Process payment for a booking
     * @param bookingId Booking ID
     * @param amount Amount to pay
     */
    void processPayment(int bookingId, double amount);
    
    /**
     * @brief Search for houses based on user criteria
     */
    void searchHouses();
    
    /**
     * @brief Display search results
     * @param searchResults Vector of houses matching search criteria
     */
    void displaySearchResults(const std::vector<House>& searchResults);

public:
    /**
     * @brief Constructor
     */
    MBomaHousingSystem();
    
    /**
     * @brief Destructor
     */
    ~MBomaHousingSystem();
    
    /**
     * @brief Run the housing management system
     */
    void run();
};

#endif // MBOMA_HOUSING_SYSTEM_H
