#ifndef USER_H
#define USER_H

#include <string>

/**
 * @brief User class to handle registration and authentication
 */
class User {
private:
    std::string name;
    std::string phone;
    std::string email;
    std::string password;
    bool isLoggedIn;

public:
    /**
     * @brief Default constructor
     */
    User();
    
    /**
     * @brief Constructor with parameters
     * @param name User's full name
     * @param phone User's phone number
     * @param email User's email address
     * @param password User's password (should be hashed in production)
     */
    User(const std::string& name, const std::string& phone, 
         const std::string& email, const std::string& password);
    
    /**
     * @brief Register a new user via console input
     * @return true if registration was successful
     */
    bool registerUser();
    
    /**
     * @brief Authenticate a user
     * @param inputEmail Email provided for login
     * @param inputPassword Password provided for login
     * @return true if credentials are valid
     */
    bool login(const std::string& inputEmail, const std::string& inputPassword);
    
    /**
     * @brief Log out the current user
     */
    void logout();
    
    /**
     * @brief Check if user is currently authenticated
     * @return Authentication status
     */
    bool isAuthenticated() const;
    
    /**
     * @brief Get user's name
     * @return User's name
     */
    std::string getName() const;
    
    /**
     * @brief Get user's email
     * @return User's email address
     */
    std::string getEmail() const;
    
    /**
     * @brief Get user's phone number
     * @return User's phone number
     */
    std::string getPhone() const;
};

#endif // USER_H
