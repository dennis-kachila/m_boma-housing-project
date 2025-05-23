# Variables and Data Types in C++

## Introduction

Variables and data types are the foundation of any C++ program. In the M-Boma Housing Project, we use various data types to represent different kinds of information, from user details to house properties. This lesson covers the fundamental data types used in the project and how they're applied in practical scenarios.

## Fundamental Data Types in C++

C++ provides several built-in data types that we use throughout the M-Boma Housing Project:

### Integer Types

Integers represent whole numbers without decimal points. In our project, we use integers for:

- User IDs
- Location IDs (counties, towns)
- Booking IDs
- Payment IDs

```cpp
// From MBomaHousingSystem.h
private:
    int currentUserId;  // Stores the ID of the currently logged-in user
    
// From Booking.h
private:
    int id;
    int userId;
    
// From Location.h
private:
    int id;
    int parentId;  // For hierarchical locations (e.g., town's parent county)
```

### Floating-Point Types

Floating-point types represent numbers with decimal points. We use these for monetary values:

- House deposit fees
- Monthly rent amounts
- Payment amounts

```cpp
// From House.h
private:
    double depositFee;
    double monthlyRent;
    
// From Payment.cpp
Payment::Payment(int id, int bookingId, double amount, const std::string& method)
    : id(id), bookingId(bookingId), amount(amount), paymentMethod(method) {
    paymentDate = getCurrentDateTime();
    receiptNumber = generateReceiptNumber();
}
```

### Character and String Types

Strings store text data. In modern C++, we use `std::string` from the Standard Library:

- User names
- Email addresses
- House types
- Addresses
- Dates and times

```cpp
// From House.h
private:
    std::string id;      // House identifier (4-character alphanumeric)
    std::string type;    // e.g., "Apartment", "Bungalow", etc.
    std::string address;
    std::string mapLink;
    std::string bookedUntil;

// From User.h
private:
    std::string name;
    std::string phone;
    std::string email;
    std::string password;
```

### Boolean Type

Boolean (`bool`) values represent true/false conditions:

- User login status
- House availability
- Booking payment status

```cpp
// From House.h
private:
    bool isAvailable;
    bool isBooked;
    
// From Booking.h
private:
    bool isPaid;
    
// From MBomaHousingSystem.h
private:
    bool isLoggedIn;
    bool useDatabase;
```

## Type Conversion

Our project often needs to convert between different data types, especially when interfacing with the database or processing user input.

### String to Numeric Conversion

When reading user input or database results:

```cpp
// From MBomaHousingSystem.cpp - Converting string input to double
std::cout << "Enter minimum monthly rent (0 for any): ";
std::string minRentStr;
std::getline(std::cin, minRentStr);
if (!minRentStr.empty()) {
    try {
        minRent = std::stod(minRentStr);  // Convert string to double
    } catch (const std::exception& e) {
        std::cout << "Invalid input, using default (0).\n";
        minRent = 0.0;
    }
}
```

### Numeric to String Conversion

When creating SQL queries or displaying information:

```cpp
// From DBConnector.cpp - Converting int to string for SQL query
std::string query = "SELECT * FROM bookings WHERE user_id = " + 
                   std::to_string(userId);  // Convert int to string
```

## String Handling

String handling is crucial for our project, especially for user input and formatting:

### String Concatenation

```cpp
// From Payment.cpp - Building a receipt
void Payment::generateReceipt(const User& user, const House& house) {
    std::string fileName = "receipt_" + std::to_string(id) + ".txt";
    std::ofstream file(fileName);
    
    if (file.is_open()) {
        file << "====== M-BOMA HOUSING RECEIPT ======\n\n";
        file << "Receipt Number: " << receiptNumber << "\n";
        file << "Date: " << paymentDate << "\n";
        file << "Customer: " << user.getName() << "\n";
        file << "Email: " << user.getEmail() << "\n";
        file << "Phone: " << user.getPhone() << "\n\n";
        file << "House Type: " << house.getType() << "\n";
        file << "Address: " << house.getAddress() << "\n";
        file << "Amount Paid: KES " << std::fixed << std::setprecision(2) << amount << "\n";
        file << "Payment Method: " << paymentMethod << "\n\n";
        file << "Thank you for choosing M-Boma Housing!\n";
        file.close();
        
        std::cout << "Receipt generated: " << fileName << "\n";
    }
}
```

### String Comparison

```cpp
// From User.cpp - Checking email and password
bool User::login(const std::string& inputEmail, const std::string& inputPassword) {
    if (email == inputEmail && password == inputPassword) {
        std::cout << "Login successful for " << name << "\n";
        return true;
    }
    return false;
}
```

### String Search and Manipulation

```cpp
// From MBomaHousingSystem.cpp - Case-insensitive search
if (house.getType().find(type) == std::string::npos) {
    matches = false;
}
```

## Constants and Literals

Constants are values that do not change during program execution. In our project:

```cpp
// From DBConfig.h - Database configuration constants
namespace DBConfig {
    const std::string DB_HOST = "localhost";
    const std::string DB_USER = "mboma_user";
    const std::string DB_PASS = "mboma_pass";
    const std::string DB_NAME = "mboma_housing";
}
```

## Type Aliases

Type aliases (`using` or `typedef`) create alternative names for existing types, making code more readable:

```cpp
// From Utils.h - Alias for a mapping type
using PaymentDetails = std::map<std::string, std::string>;

// Usage in a function signature
PaymentDetails getPaymentInfo(int bookingId);
```

## Practical Example: House ID Evolution

A significant enhancement in our project was changing house IDs from integers to 4-character alphanumeric strings. This shows the importance of choosing the right data type:

### Before (using integers):
```cpp
// Old House.h
private:
    int id;  // House identifier (numeric)

// Old House constructor
House::House(int id, const std::string& type, ...) : id(id), ...

// Old lookup
for (auto& house : houses) {
    if (house.getId() == 101) {  // Searching by numeric ID
        return &house;
    }
}
```

### After (using strings):
```cpp
// New House.h
private:
    std::string id;  // House identifier (4-character alphanumeric)

// New House constructor
House::House(const std::string& id, const std::string& type, ...) : id(id), ...

// New lookup
for (auto& house : houses) {
    if (house.getId() == "RB01") {  // Searching by string ID
        return &house;
    }
}
```

This change allowed us to:
1. Create more meaningful, location-based identifiers
2. Avoid ID collisions across different towns
3. Make house IDs more user-friendly and memorable

## Exercise: Working with Data Types

### Exercise 1: String Manipulation
Create a function that generates a unique 4-character alphanumeric house ID based on:
- First letter of town name
- First letter of house type
- Two-digit sequential number

Example: "KB01" for first Bungalow in Karen.

### Exercise 2: Type Conversion
Implement a function that formats monetary amounts with proper thousands separators and decimal places.

Input: `150000.5`
Output: `"150,000.50"`

### Exercise 3: Data Type Selection
For each of the following data items in a housing system, select the most appropriate C++ data type and explain why:
1. A user's phone number
2. House availability status
3. Monthly rent amount
4. Date of booking
5. Number of rooms in a house

## Summary

In this lesson, we've covered:
- Basic and user-defined data types in C++
- How to choose appropriate data types for different scenarios
- Type conversion techniques
- String handling operations
- The evolution of the House ID data type in our project

Understanding data types and their appropriate usage is fundamental to writing robust, maintainable C++ code. In the next lesson, we'll explore control structures and how they're used to manage program flow in our housing management system.

## Further Reading
- [C++ Data Types - cppreference.com](https://en.cppreference.com/w/cpp/language/types)
- [std::string - cppreference.com](https://en.cppreference.com/w/cpp/string/basic_string)
- [Type Conversions in C++ - cplusplus.com](http://www.cplusplus.com/doc/tutorial/typecasting/)
