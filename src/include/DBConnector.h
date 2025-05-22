#ifndef DB_CONNECTOR_H
#define DB_CONNECTOR_H

#include <mysql/mysql.h>
#include <string>
#include <vector>
#include <map>  // Add missing include for std::map
#include "User.h"
#include "House.h"
#include "Location.h"
#include "Booking.h"

/**
 * @brief Database connector class to handle MySQL operations
 */
class DBConnector {
private:
    MYSQL* conn;
    bool connected;
    std::string lastError;  // Store the last error message
    
    /**
     * @brief Execute a query and check for errors
     * @param query SQL query string
     * @return true if query was successful
     */
    bool executeQuery(const std::string& query);
    
    /**
     * @brief Set the last error message
     * @param error Error message to store
     */
    void setError(const std::string& error);
    
public:
    /**
     * @brief Constructor
     */
    DBConnector();
    
    /**
     * @brief Destructor
     */
    ~DBConnector();
    
    /**
     * @brief Get the last error message
     * @return The last error message
     */
    std::string getLastError() const;
    
    /**
     * @brief Connect to the MySQL database
     * @param host Database host
     * @param user Database username
     * @param password Database password
     * @param db Database name
     * @return true if connection successful
     */
    bool connect(const std::string& host, const std::string& user, 
                const std::string& password, const std::string& db);
    
    /**
     * @brief Close database connection
     */
    void disconnect();
    
    /**
     * @brief Check if database connection is active
     * @return true if connected
     */
    bool isConnected() const;
    
    /**
     * @brief Register a new user in the database
     * @param user User object to register
     * @return true if registration successful
     */
    bool registerUser(const User& user);
    
    /**
     * @brief Authenticate a user
     * @param email User email
     * @param password User password
     * @return true if credentials valid
     */
    bool authenticateUser(const std::string& email, const std::string& password);
    
    /**
     * @brief Load counties from the database
     * @return Vector of Location objects
     */
    std::vector<Location> loadCounties();
    
    /**
     * @brief Load users from the database
     * @return Vector of User objects
     */
    std::vector<User> loadUsers();
    
    /**
     * @brief Load towns in a county from the database
     * @param countyId County ID
     * @return Vector of Location objects
     */
    std::vector<Location> loadTowns(int countyId);
    
    /**
     * @brief Load all towns from the database
     * @return Vector of Location objects representing towns
     */
    std::vector<Location> loadAllTowns();
    
    /**
     * @brief Load houses in a town from the database
     * @param townId Town ID
     * @return Vector of House objects
     */
    std::vector<House> loadHouses(int townId);
    
    /**
     * @brief Load all houses from the database
     * @return Vector of House objects
     */
    std::vector<House> loadAllHouses();
    
    /**
     * @brief Get payment details for a house
     * @param houseId House ID
     * @param townId Town ID
     * @return Map of payment details
     */
    std::map<std::string, std::string> getPaymentDetails(const std::string& houseId, int townId);
    
    /**
     * @brief Search for houses based on criteria
     * @param type House type (optional)
     * @param minRent Minimum monthly rent (optional)
     * @param maxRent Maximum monthly rent (optional)
     * @param townId Town ID (optional)
     * @return Vector of matching House objects
     */
    std::vector<House> searchHouses(const std::string& type = "", 
                                   double minRent = 0.0,
                                   double maxRent = -1.0,  
                                   int townId = -1);
                                   
    /**
     * @brief Load bookings from the database for a specific user
     * @param userId User ID to load bookings for, or -1 for all bookings
     * @return Vector of Booking objects
     */
    std::vector<Booking> loadBookings(int userId = -1);
    
    /**
     * @brief Create a new booking in the database
     * @param userId User making the booking
     * @param houseId House being booked
     * @param townId Town where house is located
     * @return Booking ID if successful, -1 if failed
     */
    int createBooking(int userId, const std::string& houseId, int townId);
    
    /**
     * @brief Record a payment in the database
     * @param bookingId Booking that is being paid for
     * @param amount Payment amount
     * @param paymentMethod Method of payment (e.g. "M-Pesa", "Bank Transfer")
     * @return Receipt number if successful, empty string if failed
     */
    std::string recordPayment(int bookingId, double amount, const std::string& paymentMethod);
};

#endif // DB_CONNECTOR_H
