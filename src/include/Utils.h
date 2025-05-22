#ifndef UTILS_H
#define UTILS_H

#include <string>

/**
 * @brief Get current date and time as formatted string
 * @return Current date and time string
 */
std::string getCurrentDateTime();

/**
 * @brief Generate a unique receipt number
 * @return Receipt number string
 */
std::string generateReceiptNumber();

/**
 * @brief Hash a password for secure storage
 * @param password Plain text password
 * @return Hashed password string
 */
std::string hashPassword(const std::string& password);

/**
 * @brief Verify a password against its hash
 * @param password Plain text password attempt
 * @param hashedPassword Stored hashed password
 * @return true if password matches hash
 */
bool verifyPassword(const std::string& password, const std::string& hashedPassword);

/**
 * @brief Compare two strings case-insensitively
 * @param str1 First string
 * @param str2 Second string
 * @return true if strings match ignoring case
 */
bool equalsIgnoreCase(const std::string& str1, const std::string& str2);

#endif // UTILS_H
