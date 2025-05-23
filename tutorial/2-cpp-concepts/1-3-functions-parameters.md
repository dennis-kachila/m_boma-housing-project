# Functions and Parameters in C++

## Introduction

Functions are self-contained blocks of code that perform specific tasks. They improve code organization, promote reusability, and make programs easier to understand and maintain. In the M-Boma Housing Project, functions are used extensively to encapsulate operations like user authentication, house searching, and database interactions.

This lesson covers function declaration and definition, parameter passing techniques, return values, and how these concepts are applied throughout the project.

## Function Basics

### Function Declaration vs. Definition

A function declaration tells the compiler about a function's name, return type, and parameters. A function definition provides the actual body of the function.

**Declaration** (typically in a header file):
```cpp
// From House.h
std::string getId() const;
double getMonthlyRent() const;
void setAvailability(bool available);
```

**Definition** (in implementation file):
```cpp
// From House.cpp
std::string House::getId() const {
    return id;
}

double House::getMonthlyRent() const {
    return monthlyRent;
}

void House::setAvailability(bool available) {
    isAvailable = available;
}
```

### Function Components

A function consists of:
- **Return type**: The data type returned by the function (or `void` if nothing is returned)
- **Function name**: Identifier that names the function
- **Parameter list**: Input values passed to the function (optional)
- **Function body**: Code that executes when the function is called

```cpp
// From MBomaHousingSystem.cpp
House* MBomaHousingSystem::findHouse(const std::string& houseId) {
    for (auto& house : houses) {
        if (house.getId() == houseId) {
            return &house;
        }
    }
    return nullptr;
}
```

In this function:
- Return type: `House*` (pointer to a House object)
- Function name: `findHouse`
- Parameter list: `(const std::string& houseId)`
- Function body: Loop through houses and return the one with matching ID

## Parameter Passing

C++ offers several ways to pass parameters to functions, each with different implications for efficiency and data safety.

### Pass by Value

When passing by value, a copy of the parameter is created:

```cpp
// From Utils.cpp
std::string hashPassword(const std::string& password) {
    // Password is passed by const reference, but we create a local copy
    std::string result = password;
    
    // Simple hash implementation (not for production use)
    for (char& c : result) {
        c = c + 2;  // Shift each character
    }
    
    return result;
}
```

### Pass by Reference

Passing by reference allows the function to modify the original variable:

```cpp
// From House.cpp
void House::book(const std::string& until) {
    isAvailable = false;
    isBooked = true;
    bookedUntil = until;
}
```

### Pass by Const Reference

Passing by const reference prevents modification of the parameter while avoiding copying:

```cpp
// From MBomaHousingSystem.cpp
void MBomaHousingSystem::displaySearchResults(const std::vector<House>& searchResults) {
    // searchResults cannot be modified within this function
    std::cout << "\n===== SEARCH RESULTS =====\n";
    if (searchResults.empty()) {
        std::cout << "No houses found matching your criteria.\n";
        return;
    }
    
    for (const auto& house : searchResults) {
        std::cout << house.getId() << ". " << house.getType() 
                  << " in " << getTownName(house.getLocationId())
                  << " - KES " << house.getMonthlyRent() << "/month\n";
    }
}
```

### Pass by Pointer

Passing by pointer allows modification of the pointed-to object and supports null values:

```cpp
// From DBConnector.cpp
bool DBConnector::connect(const std::string& host, const std::string& user, 
                         const std::string& password, const std::string& db) {
    // Clean up previous connection if any
    if (conn != nullptr) {
        mysql_close(conn);
    }
    
    // Initialize new connection
    conn = mysql_init(nullptr);
    if (conn == nullptr) {
        setError("Failed to initialize MySQL connection");
        return false;
    }
    
    // Attempt to connect
    if (mysql_real_connect(conn, host.c_str(), user.c_str(), password.c_str(), 
                          db.c_str(), 0, nullptr, 0) == nullptr) {
        setError(mysql_error(conn));
        mysql_close(conn);
        conn = nullptr;
        return false;
    }
    
    connected = true;
    return true;
}
```

## Return Values

Functions can return data back to the calling code, which is useful for calculations, lookups, and status reporting.

### Basic Return Types

```cpp
// From Location.cpp
int Location::getId() const {
    return id;  // Returns an integer
}

std::string Location::getName() const {
    return name;  // Returns a string
}

std::string Location::getType() const {
    return type;  // Returns a string
}
```

### Returning Complex Objects

```cpp
// From DBConnector.cpp
std::vector<Location> DBConnector::loadCounties() {
    std::vector<Location> counties;
    
    if (!isConnected()) {
        setError("Database connection not available");
        return counties;  // Return empty vector
    }
    
    std::string query = "SELECT id, name FROM locations WHERE type = 'county' ORDER BY name";
    
    if (mysql_query(conn, query.c_str()) != 0) {
        setError(mysql_error(conn));
        return counties;  // Return empty vector
    }
    
    MYSQL_RES* result = mysql_store_result(conn);
    if (result == nullptr) {
        setError(mysql_error(conn));
        return counties;  // Return empty vector
    }
    
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result)) != nullptr) {
        int id = std::stoi(row[0]);
        std::string name = row[1];
        counties.emplace_back(id, name, "county");
    }
    
    mysql_free_result(result);
    return counties;  // Return populated vector
}
```

### Multiple Return Values

C++ doesn't support multiple return values directly, but we can use various approaches:

#### Using Reference Parameters

```cpp
// From Booking.cpp
bool Booking::getDetails(int& outUserId, std::string& outHouseId, std::string& outDate, bool& outPaid) const {
    outUserId = userId;
    outHouseId = houseId;
    outDate = bookingDate;
    outPaid = isPaid;
    return true;
}
```

#### Using std::pair or std::tuple

```cpp
// Example using std::pair
std::pair<bool, std::string> validateHouseId(const std::string& id) {
    if (id.length() != 4) {
        return {false, "House ID must be 4 characters"};
    }
    
    // Additional validation...
    
    return {true, "Valid house ID"};
}

// Using the function
auto [valid, message] = validateHouseId(inputId);
if (!valid) {
    std::cout << message << std::endl;
}
```

#### Using Custom Struct/Class

```cpp
// From DBConnector.h (conceptual example)
struct LoginResult {
    bool success;
    int userId;
    std::string error;
};

// Function definition
LoginResult authenticateUser(const std::string& email, const std::string& password);

// Usage
auto result = authenticateUser(email, password);
if (result.success) {
    std::cout << "Login successful. User ID: " << result.userId << std::endl;
} else {
    std::cout << "Login failed: " << result.error << std::endl;
}
```

## Function Overloading

C++ allows multiple functions with the same name but different parameter lists:

```cpp
// From MBomaHousingSystem.h
void displayHouses(int townId);
void displayHouses(int townId, double maxPrice);

// From MBomaHousingSystem.cpp
void MBomaHousingSystem::displayHouses(int townId) {
    // Display all houses in town
}

void MBomaHousingSystem::displayHouses(int townId, double maxPrice) {
    // Display houses in town with rent <= maxPrice
}
```

## Default Parameters

Default parameters allow a function to be called with fewer arguments:

```cpp
// From DBConnector.h
bool connect(const std::string& host = "localhost", 
            const std::string& user = "mboma_user", 
            const std::string& password = "mboma_pass",
            const std::string& db = "mboma_housing");

// Can be called in different ways:
dbConnector.connect();  // Uses all defaults
dbConnector.connect("remotehost");  // Custom host, default user/pass/db
dbConnector.connect("localhost", "root", "rootpass");  // Custom connection
```

## Function Scope and Lifetime

Variables declared inside a function have local scope and limited lifetime:

```cpp
// From MBomaHousingSystem.cpp
void MBomaHousingSystem::clearScreen() {
    // Local variables exist only within this function
    #ifdef _WIN32
    std::system("cls");
    #else
    std::system("clear");
    #endif
}

void MBomaHousingSystem::waitForEnter() {
    // Another function with its own scope
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
```

## Recursive Functions

Recursive functions call themselves:

```cpp
// Example: Recursive function to calculate booking duration in days
int calculateDuration(const Date& start, const Date& end) {
    if (start == end) {
        return 0;  // Base case
    }
    
    // Move start date forward by one day
    Date nextDay = start.addDays(1);
    
    // Recursive call with updated start date
    return 1 + calculateDuration(nextDay, end);
}
```

## Inline Functions

Small functions can be declared inline to suggest compiler optimization:

```cpp
// From Location.h
inline bool isCounty() const {
    return type == "county";
}

inline bool isTown() const {
    return type == "town";
}
```

## Function Pointers and Function Objects

Advanced C++ allows functions to be passed to other functions:

```cpp
// From MBomaHousingSystem.cpp
void MBomaHousingSystem::sortHouses(std::vector<House>& houses, bool (*compareFunc)(const House&, const House&)) {
    std::sort(houses.begin(), houses.end(), compareFunc);
}

// Comparison functions
bool compareByPrice(const House& a, const House& b) {
    return a.getMonthlyRent() < b.getMonthlyRent();
}

bool compareByType(const House& a, const House& b) {
    return a.getType() < b.getType();
}

// Usage
sortHouses(searchResults, compareByPrice);  // Sort by price
sortHouses(searchResults, compareByType);   // Sort by type
```

## Lambda Functions (Modern C++)

C++11 introduced lambda functions for inline anonymous functions:

```cpp
// From MBomaHousingSystem.cpp
void MBomaHousingSystem::searchHouses() {
    // Get search criteria from user
    std::string type;
    double minRent = 0.0, maxRent = 0.0;
    int townId = -1;
    
    // ... get input from user ...
    
    // Using lambda function to filter houses
    auto matchesCriteria = [&](const House& house) -> bool {
        // Match town if specified
        if (townId > 0 && house.getLocationId() != townId) {
            return false;
        }
        
        // Match type if specified
        if (!type.empty() && !equalsIgnoreCase(house.getType(), type)) {
            return false;
        }
        
        // Match price range if specified
        if (minRent > 0 && house.getMonthlyRent() < minRent) {
            return false;
        }
        
        if (maxRent > 0 && house.getMonthlyRent() > maxRent) {
            return false;
        }
        
        return true;
    };
    
    // Apply the filter
    std::vector<House> results;
    for (const auto& house : houses) {
        if (matchesCriteria(house)) {
            results.push_back(house);
        }
    }
    
    // Display results
    displaySearchResults(results);
}
```

## Practical Example: User Authentication

Let's examine how functions work together in the user authentication system:

```cpp
// From MBomaHousingSystem.cpp
bool MBomaHousingSystem::loginUser() {
    std::string email, password;
    std::cout << "\n===== LOGIN =====\n";
    std::cout << "Email: ";
    std::getline(std::cin, email);
    std::cout << "Password: ";
    std::getline(std::cin, password);
    
    if (useDatabase && dbConnector && dbConnector->isConnected()) {
        // Authenticate against database
        if (dbConnector->authenticateUser(email, password)) {
            int userId = dbConnector->getUserId(email);
            if (userId > 0) {
                currentUserId = userId;
                isLoggedIn = true;
                std::cout << "Login successful!\n";
                return true;
            }
        }
    } else {
        // Fallback to local authentication
        for (const auto& user : users) {
            if (user.getEmail() == email && user.verifyPassword(password)) {
                currentUserId = user.getId();
                isLoggedIn = true;
                std::cout << "Login successful!\n";
                return true;
            }
        }
    }
    
    std::cout << "Invalid email or password. Please try again.\n";
    return false;
}

// From User.cpp
bool User::verifyPassword(const std::string& inputPassword) const {
    return ::verifyPassword(inputPassword, password);
}

// From Utils.cpp
bool verifyPassword(const std::string& password, const std::string& hashedPassword) {
    // Hash the input password and compare with stored hash
    std::string hashedInput = hashPassword(password);
    return hashedInput == hashedPassword;
}

std::string hashPassword(const std::string& password) {
    // In a real application, use a proper cryptographic hash function
    // This is a simplified example
    std::string result = password;
    for (char& c : result) {
        c = c + 2;  // Shift each character
    }
    return result;
}
```

This example demonstrates:
1. Functions calling other functions (`loginUser` calls `verifyPassword` which calls `hashPassword`)
2. Different parameter passing techniques (by value, by reference)
3. Boolean return values for success/failure indication
4. Function overloading (`verifyPassword` exists both as a member function and a global function)
5. Encapsulation of business logic in specific functions

## Exercise: Function Implementation

### Exercise 1: Parameter Passing
Implement a function that takes a house object by reference and calculates the total cost for a specified number of months:

```cpp
double calculateTotalCost(const House& house, int months, bool includeDeposit);
```

### Exercise 2: Function Overloading
Create overloaded functions to search for houses by different criteria:

```cpp
// Find houses by type (e.g., "Apartment")
std::vector<House> findHouses(const std::vector<House>& houses, const std::string& type);

// Find houses by price range
std::vector<House> findHouses(const std::vector<House>& houses, double minPrice, double maxPrice);

// Find houses by location
std::vector<House> findHouses(const std::vector<House>& houses, int townId);
```

### Exercise 3: Lambda Functions
Use a lambda function to create a flexible house filter function:

```cpp
// Using a lambda function as callback
std::vector<House> filterHouses(
    const std::vector<House>& houses,
    std::function<bool(const House&)> filterFunction);
```

## Summary

In this lesson, we've covered:
- Function declaration and definition
- Parameter passing techniques (by value, reference, const reference, pointer)
- Return values and techniques for returning multiple values
- Function overloading for versatile interfaces
- Default parameters for simplified function calls
- Function scope and lifetime of local variables
- Advanced concepts like recursive functions, inline functions, function pointers, and lambda functions

Functions are the building blocks of modular, maintainable code. In the M-Boma Housing Project, well-designed functions allow us to separate concerns, promote code reuse, and create a more flexible and maintainable system.

## Further Reading
- [C++ Functions - cppreference.com](https://en.cppreference.com/w/cpp/language/functions)
- [Parameter Passing - cplusplus.com](http://www.cplusplus.com/doc/tutorial/functions/)
- [Lambda Expressions - Microsoft Docs](https://docs.microsoft.com/en-us/cpp/cpp/lambda-expressions-in-cpp)
