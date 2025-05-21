#ifndef DB_CONFIG_H
#define DB_CONFIG_H

#include <string>

namespace DBConfig {
    // Database connection parameters
    const std::string DB_HOST = "localhost";
    const std::string DB_USER = "root";  // Change to your MySQL username
    const std::string DB_PASS = "";      // Change to your MySQL password
    const std::string DB_NAME = "mboma_housing";
}

#endif // DB_CONFIG_H
