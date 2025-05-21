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

#endif // UTILS_H
