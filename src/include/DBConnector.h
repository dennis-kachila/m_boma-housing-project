#ifndef DB_CONNECTOR_H
#define DB_CONNECTOR_H

#include <mysql/mysql.h>
#include <string>
#include <vector>
#include "User.h"
#include "House.h"
#include "Location.h"

/**
 * @brief Database connector class to handle MySQL operations
 */
class DBConnector {
private:
    MYSQL* conn;
    bool connected;
    
    /**
     * @brief Execute a query and check for errors
     * @param query SQL query string
     * @return true if query was successful
     */
    bool executeQuery(const std::string& query);
    
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
     * @brief Load all counties from the database
     * @return Vector of Location objects
     */
    std::vector<Location> loadCounties();
    
    /**
     * @brief Load towns in a county from the database
     * @param countyId County ID
     * @return Vector of Location objects
     */
    std::vector<Location> loadTowns(int countyId);
    
    /**
     * @brief Load houses in a town from the database
     * @param townId Town ID
     * @return Vector of House objects
     */
    std::vector<House> loadHouses(int townId);
    
    /**
     * @brief Get payment details for a house
     * @param houseId House ID
     * @param townId Town ID
     * @return Map of payment details
     */
    std::map<std::string, std::string> getPaymentDetails(int houseId, int townId);
};

#endif // DB_CONNECTOR_H
