#ifndef DB_CONFIG_H
#define DB_CONFIG_H

#include <string>

namespace DBConfig {
    // Database connection parameters
    // IMPORTANT: Update these values based on your MySQL configuration
    const std::string DB_HOST = "localhost";
    const std::string DB_USER = "mboma_user";  // MySQL username
    const std::string DB_PASS = "mboma_password";  // MySQL password
    const std::string DB_NAME = "mboma_housing";
    
    // Connection retry settings
    const int CONNECTION_RETRY_ATTEMPTS = 3;
    const int CONNECTION_RETRY_DELAY_MS = 1000;
}

#endif // DB_CONFIG_H
