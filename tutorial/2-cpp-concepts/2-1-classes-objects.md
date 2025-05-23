# Classes and Objects in C++

## Introduction

Object-Oriented Programming (OOP) is a powerful paradigm that organizes code around "objects" - data structures that contain both data (attributes) and code (methods). C++ is a multi-paradigm language with strong support for OOP concepts, allowing developers to create well-structured, maintainable applications.

The M-Boma Housing Project is built entirely on object-oriented principles. This lesson introduces classes and objects, explaining how they're implemented throughout the project.

## Classes as Blueprints

A class is a blueprint for creating objects. It defines:
- **Data members** (attributes/properties) 
- **Member functions** (methods)
- **Access control** (public, private, protected)

### Basic Class Structure

Here's the basic structure of a class in our project:

```cpp
// From House.h
class House {
private:
    // Data members (attributes)
    std::string id;
    std::string type;
    double depositFee;
    double monthlyRent;
    int locationId;
    std::string address;
    std::string mapLink;
    bool isAvailable;
    bool isBooked;
    std::string bookedUntil;

public:
    // Constructor
    House(const std::string& id, const std::string& type, double depositFee, double monthlyRent,
          int locationId, const std::string& address, const std::string& mapLink);
    
    // Public methods (behaviors)
    std::string getId() const;
    std::string getType() const;
    // More getter methods...
    
    void setAvailability(bool available);
    void book(const std::string& until);
    void unbook();
};
```

## Objects as Class Instances

Objects are instances of classes. They represent specific entities with their own state:

```cpp
// Creating House objects
House house1("RB01", "Bungalow", 50000.0, 25000.0, 101, "123 Runda Way", "maps.google.com/123");
House house2("KA01", "Apartment", 20000.0, 15000.0, 201, "456 Kahawa Ave", "maps.google.com/456");

// Accessing object properties through methods
std::cout << "House 1: " << house1.getType() << " for KES " << house1.getMonthlyRent() << std::endl;
std::cout << "House 2: " << house2.getType() << " for KES " << house2.getMonthlyRent() << std::endl;

// Manipulating object state
house1.book("2025-06-30");
if (!house1.getAvailability()) {
    std::cout << "House 1 is now booked until " << house1.getBookedUntil() << std::endl;
}
```

## Class Members

### Data Members (Attributes)

Data members store the state of objects:

```cpp
// From User.h
private:
    int id;
    std::string name;
    std::string phone;
    std::string email;
    std::string password;  // Stored as hash
```

### Member Functions (Methods)

Member functions define behaviors:

```cpp
// From User.h
public:
    // Input/output operations
    bool registerUser();
    bool login(const std::string& email, const std::string& password);
    
    // Getters
    int getId() const;
    std::string getName() const;
    std::string getPhone() const;
    std::string getEmail() const;
    
    // Utility
    bool verifyPassword(const std::string& inputPassword) const;
```

## Access Control

Access specifiers control visibility and access to class members:

### Private Members

Private members are accessible only within the class:

```cpp
// From Booking.h
private:
    int id;
    int userId;
    std::string houseId;
    int locationId;
    std::string bookingDate;
    bool isPaid;
```

### Public Members

Public members are accessible from anywhere:

```cpp
// From Booking.h
public:
    Booking(int id, int userId, const std::string& houseId, int locationId);
    
    int getId() const;
    int getUserId() const;
    std::string getHouseId() const;
    int getLocationId() const;
    std::string getBookingDate() const;
    bool getPaymentStatus() const;
    
    void markAsPaid();
```

### Protected Members

Protected members are accessible within the class and its subclasses:

```cpp
// Example from an authentication base class (conceptual)
class AuthBase {
protected:
    bool isAuthenticated;
    std::string currentUserToken;
    
    bool validateCredentials(const std::string& username, const std::string& password);
};

// Derived class can access protected members
class UserAuth : public AuthBase {
public:
    bool login(const std::string& username, const std::string& password) {
        if (validateCredentials(username, password)) {
            isAuthenticated = true;
            return true;
        }
        return false;
    }
};
```

## Constructors and Destructors

### Constructors

Constructors initialize objects when they are created:

```cpp
// Declaration in House.h
House(const std::string& id, const std::string& type, double depositFee, double monthlyRent,
      int locationId, const std::string& address, const std::string& mapLink);

// Definition in House.cpp
House::House(const std::string& id, const std::string& type, double depositFee, double monthlyRent,
      int locationId, const std::string& address, const std::string& mapLink)
    : id(id), type(type), depositFee(depositFee), monthlyRent(monthlyRent),
      locationId(locationId), address(address), mapLink(mapLink),
      isAvailable(true), isBooked(false), bookedUntil("") {}
```

### Member Initialization Lists

Initialization lists efficiently initialize members:

```cpp
// From Payment.cpp
Payment::Payment(int id, int bookingId, double amount, const std::string& method)
    : id(id), bookingId(bookingId), amount(amount), paymentMethod(method) {
    paymentDate = getCurrentDateTime();
    receiptNumber = generateReceiptNumber();
}
```

### Default Constructors

Default constructors take no parameters:

```cpp
// From User.h
User(); // Declaration of default constructor

// From User.cpp
User::User() : id(-1) {} // Definition of default constructor
```

### Destructors

Destructors clean up resources when objects are destroyed:

```cpp
// From DBConnector.h
~DBConnector();

// From DBConnector.cpp
DBConnector::~DBConnector() {
    disconnect();
}
```

### Resource Management

Proper constructors and destructors implement RAII (Resource Acquisition Is Initialization):

```cpp
// From MBomaHousingSystem.cpp
MBomaHousingSystem::MBomaHousingSystem() : dbConnector(nullptr), useDatabase(false),
                                         currentUserId(-1), isLoggedIn(false) {
    // Initialize database connection
    dbConnector = new DBConnector();
    if (dbConnector->connect()) {
        useDatabase = true;
        initializeData();
    }
}

MBomaHousingSystem::~MBomaHousingSystem() {
    // Clean up resources
    if (dbConnector) {
        delete dbConnector;
        dbConnector = nullptr;
    }
}
```

## Member Functions

### Method Declarations vs. Definitions

Methods are declared in header files and defined in source files:

```cpp
// Declaration in Location.h
int getId() const;

// Definition in Location.cpp
int Location::getId() const {
    return id;
}
```

### Constant Member Functions

The `const` keyword indicates methods that don't modify the object:

```cpp
// From House.h - These methods don't modify the House object
std::string getId() const;
std::string getType() const;
double getMonthlyRent() const;
```

### Static Member Functions

Static member functions belong to the class, not specific instances:

```cpp
// Example of potential static method for User class
// User.h
static bool isValidEmail(const std::string& email);

// User.cpp
bool User::isValidEmail(const std::string& email) {
    // Email validation logic
    return email.find('@') != std::string::npos;
}

// Usage
if (User::isValidEmail(inputEmail)) {
    // Process valid email
}
```

## Encapsulation

Encapsulation is the bundling of data with methods that operate on that data, restricting direct access to some components:

```cpp
// From House.h and House.cpp
class House {
private:
    bool isAvailable;
    bool isBooked;
    std::string bookedUntil;
    
public:
    bool getAvailability() const {
        return isAvailable;
    }
    
    bool getBookingStatus() const {
        return isBooked;
    }
    
    void book(const std::string& until) {
        isAvailable = false;
        isBooked = true;
        bookedUntil = until;
    }
    
    void unbook() {
        isAvailable = true;
        isBooked = false;
        bookedUntil = "";
    }
};
```

Benefits of encapsulation:
1. **Information hiding**: Internal implementation details are hidden
2. **Controlled access**: Data is manipulated only through defined methods
3. **Flexibility**: Internal implementation can change without affecting external code

## Object Relationships

Objects can relate to each other in various ways:

### Association

Association represents a "uses" relationship:

```cpp
// From MBomaHousingSystem.cpp
void MBomaHousingSystem::processPayment(int bookingId, double amount) {
    // Find the booking
    Booking* booking = nullptr;
    for (auto& b : bookings) {
        if (b.getId() == bookingId) {
            booking = &b;
            break;
        }
    }
    
    if (!booking) {
        std::cout << "Booking not found.\n";
        return;
    }
    
    // Create payment record
    Payment payment(getNextId("payment"), bookingId, amount, "Cash");
    payments.push_back(payment);
    
    // Mark booking as paid
    booking->markAsPaid();
    
    // Generate receipt
    User* user = getCurrentUser();
    House* house = findHouse(booking->getHouseId());
    
    if (user && house) {
        payment.generateReceipt(*user, *house);
    }
}
```

In this example, `MBomaHousingSystem` uses `Payment`, `Booking`, `User`, and `House` objects.

### Composition

Composition represents a "has-a" relationship where the contained object cannot exist without the container:

```cpp
// Conceptual example of composition
class Address {
private:
    std::string street;
    std::string city;
    std::string zipCode;

public:
    Address(const std::string& street, const std::string& city, const std::string& zipCode)
        : street(street), city(city), zipCode(zipCode) {}
};

class PropertyListing {
private:
    std::string id;
    Address address;  // Composition: PropertyListing "has-a" Address
    double price;

public:
    PropertyListing(const std::string& id, const std::string& street, 
                   const std::string& city, const std::string& zipCode, double price)
        : id(id), address(street, city, zipCode), price(price) {}
};
```

### Aggregation

Aggregation is a weaker form of composition, representing a "has-a" relationship where the contained object can exist independently:

```cpp
// From MBomaHousingSystem.h
class MBomaHousingSystem {
private:
    std::vector<User> users;
    std::vector<Location> locations;
    std::vector<House> houses;
    std::vector<Booking> bookings;
    std::vector<Payment> payments;
    
    DBConnector* dbConnector;  // Aggregation: MBomaHousingSystem "has-a" DBConnector
};
```

## Object Lifecycle

Objects follow a lifecycle from creation to destruction:

1. **Construction**: Allocation and initialization
2. **Usage**: Operations performed on the object
3. **Destruction**: Resource cleanup and memory deallocation

```cpp
// Object lifecycle example
{
    // 1. Construction
    House house("KA01", "Apartment", 20000, 15000, 201, "123 Kahawa Rd", "maps.link");
    
    // 2. Usage
    std::cout << "House: " << house.getType() << " at " << house.getAddress() << std::endl;
    house.book("2025-06-30");
    
    // 3. Destruction (automatic at end of scope)
} // house destructor called here
```

## Practical Example: The House Class

Let's examine how the House class is implemented and used in our project:

```cpp
// From House.h
#ifndef HOUSE_H
#define HOUSE_H

#include <string>

/**
 * @brief House class to represent available houses
 */
class House {
private:
    std::string id;
    std::string type;        // e.g., "Apartment", "Bungalow", etc.
    double depositFee;
    double monthlyRent;
    int locationId;          // Town ID
    std::string address;
    std::string mapLink;
    bool isAvailable;
    bool isBooked;
    std::string bookedUntil;

public:
    /**
     * @brief Constructor with parameters
     */
    House(const std::string& id, const std::string& type, double depositFee, double monthlyRent,
          int locationId, const std::string& address, const std::string& mapLink);
    
    // Accessor methods
    std::string getId() const;
    std::string getType() const;
    double getDepositFee() const;
    double getMonthlyRent() const;
    int getLocationId() const;
    std::string getAddress() const;
    std::string getMapLink() const;
    bool getAvailability() const;
    bool getBookingStatus() const;
    std::string getBookedUntil() const;
    
    // Mutator methods
    void setAvailability(bool available);
    void book(const std::string& until);
    void unbook();
};

#endif // HOUSE_H
```

```cpp
// From House.cpp
#include "include/House.h"

House::House(const std::string& id, const std::string& type, double depositFee, double monthlyRent,
      int locationId, const std::string& address, const std::string& mapLink)
    : id(id), type(type), depositFee(depositFee), monthlyRent(monthlyRent),
      locationId(locationId), address(address), mapLink(mapLink),
      isAvailable(true), isBooked(false), bookedUntil("") {}

std::string House::getId() const {
    return id;
}

std::string House::getType() const {
    return type;
}

double House::getDepositFee() const {
    return depositFee;
}

double House::getMonthlyRent() const {
    return monthlyRent;
}

int House::getLocationId() const {
    return locationId;
}

std::string House::getAddress() const {
    return address;
}

std::string House::getMapLink() const {
    return mapLink;
}

bool House::getAvailability() const {
    return isAvailable;
}

bool House::getBookingStatus() const {
    return isBooked;
}

std::string House::getBookedUntil() const {
    return bookedUntil;
}

void House::setAvailability(bool available) {
    isAvailable = available;
    if (!available) {
        isBooked = true;
    }
}

void House::book(const std::string& until) {
    isAvailable = false;
    isBooked = true;
    bookedUntil = until;
}

void House::unbook() {
    isAvailable = true;
    isBooked = false;
    bookedUntil = "";
}
```

Usage in the system:

```cpp
// From MBomaHousingSystem.cpp
void MBomaHousingSystem::displayHouses(int townId) {
    std::cout << "\n===== HOUSES IN " << getTownName(townId) << " =====\n";
    int count = 0;
    for (const auto& house : houses) {
        if (house.getLocationId() == townId) {
            std::cout << house.getId() << ". " << house.getType() 
                      << " - KES " << house.getMonthlyRent() << "/month\n";
            count++;
        }
    }
    
    if (count == 0) {
        std::cout << "No houses found in this town.\n";
    }
}

House* MBomaHousingSystem::findHouse(const std::string& houseId) {
    for (auto& house : houses) {
        if (house.getId() == houseId) {
            return &house;
        }
    }
    return nullptr;
}
```

## Object-Oriented Design in the Project

Our project uses OOP concepts to model real-world entities and their relationships:

### Entity Classes

- **User**: Represents a customer who can browse and book houses
- **House**: Represents a property available for rent
- **Location**: Represents geographical divisions (counties and towns)
- **Booking**: Represents a reservation of a house by a user
- **Payment**: Represents a financial transaction for a booking

### Service Classes

- **MBomaHousingSystem**: Coordinates the overall system operations
- **DBConnector**: Manages database interactions

### Class Relationships

- **MBomaHousingSystem aggregates** User, House, Location, Booking, and Payment objects
- **Booking associates** with User and House 
- **Payment associates** with Booking
- **House associates** with Location

This object-oriented design provides a clear structure that reflects the domain model of a housing management system.

## Exercise: Class Design and Implementation

### Exercise 1: Property Amenity Class
Design a class to represent amenities in a house:

```cpp
class Amenity {
    // TODO: Define data members and methods to represent
    // amenities like WiFi, parking, security, water, etc.
};
```

### Exercise 2: House Rating System
Extend the House class to include a rating system:

```cpp
class HouseRating {
    // TODO: Define data members and methods for a rating system
    // that allows users to rate houses and stores the average rating
};
```

### Exercise 3: Implement a Utility Class
Create a static utility class for housing-related calculations:

```cpp
class RentalCalculator {
public:
    // TODO: Implement static methods for:
    // - Calculating pro-rated rent for partial months
    // - Calculating total cost including deposit
    // - Estimating utility costs based on house type
};
```

## Summary

In this lesson, we've covered:
- Classes as blueprints and objects as instances
- Data members (attributes) and member functions (methods)
- Access control with private, public, and protected specifiers
- Constructors and destructors for object initialization and cleanup
- Member initialization lists for efficient initialization
- Constant member functions that don't modify object state
- Encapsulation for information hiding and controlled access
- Object relationships: association, composition, and aggregation
- The complete object lifecycle
- Object-oriented design in the M-Boma Housing Project

Classes and objects form the foundation of our project's structure, allowing us to model real-world entities and their interactions in a maintainable way. This object-oriented approach provides a clear separation of concerns, encapsulation of implementation details, and a flexible foundation for future enhancements.

## Further Reading
- [C++ Classes - cppreference.com](https://en.cppreference.com/w/cpp/language/classes)
- [Object Relationships - cplusplus.com](http://www.cplusplus.com/doc/tutorial/classes2/)
- [Object-Oriented Design Principles](https://www.oodesign.com/)
