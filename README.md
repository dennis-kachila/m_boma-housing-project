# m_boma Housing Project

## Overview
m_boma Housing Project is a C++ application designed to help tenants find and book their desired houses for rent across various counties. The project was developed as part of a Computer Programming Unit at the university.

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Project History and Archive](#project-history-and-archive)
- [Project Structure](#project-structure)
- [Setup & Installation](#setup--installation)
- [Usage](#usage)
- [Troubleshooting](#troubleshooting)
- [Common Code Issues and Fixes](#common-code-issues-and-fixes)
- [Database Configuration Details](#database-configuration-details)
- [Security Considerations](#security-considerations)
- [Project Dependencies](#project-dependencies)
- [Running in Production](#running-in-production)
- [Contributing](#contributing)
- [Future Improvements](#future-improvements)
- [License](#license)

## Features
- User registration (Name, Phone, Email, Password) with secure password hashing
- Navigation through sampled counties (e.g., Nairobi, Mombasa, Kisumu)
- View main towns and available houses in each town
- Display house details: type, deposit fee, monthly rent, and map link
- Advanced house search functionality by type, price range, or location
- Multiple payment options (M-Pesa, bank)
- Receipt generation for payments
- House booking with a 30-day grace period
- Database integration for persistent storage
- Error handling and data validation

## Project History and Archive

The `/Archive` directory contains the original version of the project that was developed during university studies after learning C/C++ on February 17, 2020. This early work has been preserved to document the evolution of the project and to appreciate the initial implementation that laid the foundation for the current system.

The archived version represents my first significant programming project after learning the basics of C/C++, showcasing the application of fundamental programming concepts in a real-world context. It follows a more straightforward, monolithic design typical of early programming projects.

Key improvements in the current implementation over the archived university project:
- Refactored from a monolithic design to a modular, object-oriented architecture
- Enhanced database schema with proper relationships and constraints
- Improved user interface and interaction flow
- Added comprehensive error handling and validation
- Implemented secure password handling and SQL injection protection
- Created detailed documentation and setup instructions

The archived version provides valuable historical context for understanding the project's origins and my personal development journey as a programmer.

## Project Structure
```
├── Archive/                         # Previous version of the project
│   ├── README.md                    # Original project description
│   ├── database/                    # Original database schema
│   │   └── housing_database.sql
│   └── source_code/                 # Original source code implementation
│       ├── boma_main.cpp
│       ├── boma.cpp
│       └── boma.h
├── database/
│   └── create_database.sql         # Enhanced SQL database schema
├── src/
│   ├── main.cpp                    # Main application entry point
│   ├── MBomaHousingSystem.cpp      # Core system implementation
│   ├── User.cpp                    # User class implementation
│   ├── Location.cpp                # Location class implementation
│   ├── House.cpp                   # House class implementation
│   ├── Booking.cpp                 # Booking class implementation  
│   ├── Payment.cpp                 # Payment class implementation
│   ├── DBConnector.cpp             # Database connector implementation
│   ├── Utils.cpp                   # Utility functions
│   └── include/                    # Header files
│       ├── MBomaHousingSystem.h
│       ├── User.h
│       ├── Location.h
│       ├── House.h
│       ├── Booking.h
│       ├── Payment.h
│       ├── DBConnector.h
│       ├── DBConfig.h
│       └── Utils.h
├── Makefile                        # Build configuration
└── README.md                       # Project documentation
```

## Setup & Installation

### Prerequisites
1. Clone the repository:
   ```bash
   git clone <repository-url>
   cd m_boma-housing-project
   ```

### MySQL Server Setup

1. Check if MySQL server is installed and running:
   ```bash
   systemctl status mysql
   ```

2. If MySQL is not installed, install it:
   ```bash
   sudo apt-get update
   sudo apt-get install -y mysql-server
   ```

3. If MySQL is installed but not running, start it:
   ```bash
   sudo systemctl start mysql
   sudo systemctl enable mysql
   ```

4. Install required development libraries:
   ```bash
   sudo apt-get install -y libmysqlclient-dev libssl-dev
   ```

### Database Setup

1. Create the database, user, and grant permissions:
   ```bash
   sudo mysql -e "CREATE DATABASE IF NOT EXISTS mboma_housing; \
                  CREATE USER IF NOT EXISTS 'mboma_user'@'localhost' IDENTIFIED BY 'mboma_password'; \
                  GRANT ALL PRIVILEGES ON mboma_housing.* TO 'mboma_user'@'localhost'; \
                  FLUSH PRIVILEGES;"
   ```

2. Import the database schema:
   ```bash
   mysql -umboma_user -pmboma_password < database/create_database.sql
   ```

3. Verify the database connection credentials in `src/include/DBConfig.h`:
   ```cpp
   const std::string DB_HOST = "localhost";
   const std::string DB_USER = "mboma_user";
   const std::string DB_PASS = "mboma_password";
   const std::string DB_NAME = "mboma_housing";
   ```

### Build the Project

1. Create required directories:
   ```bash
   mkdir -p obj bin
   ```

2. Compile the project:
   ```bash
   make clean && make
   ```

## Usage

1. Run the compiled program:
   ```bash
   ./bin/mboma
   ```

Follow the on-screen instructions to:
1. Register a new account or login with existing credentials
2. Browse through counties and towns to find available houses
3. View detailed information about houses including price and location
4. Book houses and make payments using different methods
5. Generate and view payment receipts

## Troubleshooting

### Database Connection Issues

1. Verify MySQL server is running:
   ```bash
   systemctl status mysql
   ```

2. Check database credentials in `src/include/DBConfig.h`:
   ```cpp
   const std::string DB_HOST = "localhost";
   const std::string DB_USER = "mboma_user";
   const std::string DB_PASS = "mboma_password";
   const std::string DB_NAME = "mboma_housing";
   ```

3. Verify the user has proper permissions:
   ```bash
   sudo mysql -e "SHOW GRANTS FOR 'mboma_user'@'localhost';"
   ```

4. Verify database schema:
   ```bash
   mysql -umboma_user -pmboma_password -e "USE mboma_housing; SHOW TABLES;"
   ```

### Compilation Errors

1. Missing header files:
   - Ensure all required packages are installed:
     ```bash
     sudo apt-get install -y libmysqlclient-dev libssl-dev
     ```

2. Makefile issues:
   - Verify the Makefile has proper tab indentation (not spaces)
   - Ensure target directories exist:
     ```bash
     mkdir -p obj bin
     ```

3. MySQL C API errors:
   - Check MySQL C API development headers:
     ```bash
     ls -l /usr/include/mysql
     ```
   - If missing, reinstall:
     ```bash
     sudo apt-get install --reinstall libmysqlclient-dev
     ```

### Runtime Errors

1. Database schema inconsistencies:
   - Rerun the database creation script:
     ```bash
     mysql -umboma_user -pmboma_password < database/create_database.sql
     ```

2. Permission errors:
   - Ensure the binary is executable:
     ```bash
     chmod +x bin/mboma
     ```

## Common Code Issues and Fixes

When working with this project, you might encounter the following code issues:

### Missing Header Includes

The following headers are required in `DBConnector.cpp`:
```cpp
#include <map>       // For std::map
#include <sstream>   // For std::stringstream
#include <iomanip>   // For std::put_time
```

The following header is required in `DBConnector.h`:
```cpp
#include <map>       // For std::map
```

### Variable Declaration in Switch Statements

When using switch statements with case labels, ensure variables are declared outside the switch block to avoid "jump to case label" errors:

```cpp
// Incorrect
switch(choice) {
    case 1:
        std::string name;  // Variable declaration within a case
        // ...
        break;
}

// Correct
std::string name;  // Declare outside switch
switch(choice) {
    case 1:
        // Use the variable
        break;
}
```

### Constructor Initialization Order

Ensure member variables are initialized in the same order they are declared in the class to avoid reordering warnings:

```cpp
// In header: DBConnector* dbConnector; followed by bool isLoggedIn;

// Incorrect initialization order
Constructor() : isLoggedIn(false), dbConnector(nullptr) { }

// Correct initialization order
Constructor() : dbConnector(nullptr), isLoggedIn(false) { }
```

## Database Configuration Details

The database configuration is stored in `src/include/DBConfig.h`:

```cpp
namespace DBConfig {
    // Database connection parameters
    const std::string DB_HOST = "localhost";
    const std::string DB_USER = "mboma_user";  // MySQL username
    const std::string DB_PASS = "mboma_password";  // MySQL password
    const std::string DB_NAME = "mboma_housing";
    
    // Connection retry settings
    const int CONNECTION_RETRY_ATTEMPTS = 3;
    const int CONNECTION_RETRY_DELAY_MS = 1000;
}
```

The application is configured to retry the database connection up to 3 times with a 1-second delay between attempts if the initial connection fails.

## Security Considerations

1. **Password Hashing**: User passwords are hashed using SHA-256 via OpenSSL before storage.

2. **SQL Injection Prevention**: User inputs are escaped before being used in SQL queries.

3. **Database Credentials**: Access to the database is restricted to a dedicated user with minimal privileges.

## Project Dependencies

- **C++ Compiler**: g++ with C++11 support
- **Build System**: Make
- **Database**: MySQL 5.7 or higher
- **Libraries**:
  - libmysqlclient (MySQL C API)
  - libssl (OpenSSL for password hashing)

## Running in Production

For a production environment, consider the following additional steps:

1. Use a stronger password for the database user.

2. Configure proper firewall rules to protect the MySQL server.

3. Set up regular database backups:
   ```bash
   # Manual backup
   mysqldump -umboma_user -pmboma_password mboma_housing > backup.sql
   
   # Automated backup with cron
   # Add to crontab: 0 2 * * * mysqldump -umboma_user -pmboma_password mboma_housing > /backup/mboma_$(date +\%Y\%m\%d).sql
   ```

4. Consider implementing a more secure authentication system with salted password hashing.

## Contributing
Contributions are welcome! Please fork the repository and submit a pull request. For major changes, open an issue first to discuss your ideas.

## Future Improvements
The following features and improvements are planned for future releases:

1. **Enhanced Security**
   - Implement JWT authentication for secure API access
   - Add role-based access control for admin users
   - Add brute force protection for login attempts

2. **User Interface Improvements**
   - Develop a web interface using a modern framework
   - Add mobile compatibility for on-the-go house hunting
   - Implement real-time notifications for booking status

3. **Additional Features**
   - Integration with payment gateways for real transactions
   - Landlord accounts for property management
   - Property rating and review system
   - Photo gallery for house listings

4. **Performance Optimizations**
   - Database indexing for faster queries
   - Caching frequently accessed data
   - Optimized search algorithms

5. **Testing**
   - Comprehensive unit tests for all classes
   - Integration tests for the database connector
   - Performance benchmarking

## License
This project is for educational purposes.