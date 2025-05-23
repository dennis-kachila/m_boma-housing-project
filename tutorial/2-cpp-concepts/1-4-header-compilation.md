# Header Files and Compilation in C++

## Introduction

Understanding header files and the compilation process is essential for building structured C++ applications. The M-Boma Housing Project follows a modular architecture with multiple source and header files that work together to form a complete system. This lesson explains how header files organize code and how the compilation process works, including how our project uses a Makefile to simplify building.

## Header Files

Header files (`.h` or `.hpp` files) contain declarations that can be shared across multiple source files, promoting code reuse and modular design.

### Purpose of Header Files

In C++, header files serve several important purposes:

1. **Declaration of classes, functions, and variables**
2. **Sharing code across multiple source files**
3. **Separating interface from implementation**
4. **Reducing compilation time**

### Header File Structure

A typical header file in our project follows this structure:

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

### Include Guards

Include guards prevent multiple inclusions of the same header, which would cause redefinition errors:

```cpp
#ifndef HOUSE_H
#define HOUSE_H

// Header content here...

#endif // HOUSE_H
```

Alternatively, some projects use the more modern `#pragma once` directive:

```cpp
#pragma once

// Header content here...
```

### Forward Declarations

Forward declarations can reduce dependencies between header files:

```cpp
// From MBomaHousingSystem.h
#ifndef MBOMA_HOUSING_SYSTEM_H
#define MBOMA_HOUSING_SYSTEM_H

#include <vector>
#include <string>
#include <map>
#include "User.h"
#include "Location.h"
#include "House.h"
#include "Booking.h"
#include "Payment.h"

// Forward declaration for DBConnector
class DBConnector;

/**
 * @brief Main housing management system class
 */
class MBomaHousingSystem {
    // Class definition...
};

#endif // MBOMA_HOUSING_SYSTEM_H
```

By using a forward declaration for `DBConnector`, we avoid including the entire `DBConnector.h` header, reducing dependencies and potentially improving compilation time.

### Class Hierarchies and Header Dependencies

Let's examine the header structure of our project:

```
src/include/
├── Booking.h        # Depends on <string>
├── DBConfig.h       # No dependencies
├── DBConnector.h    # Depends on <mysql/mysql.h>, <string>, <vector>, <map>, "User.h", "House.h", "Location.h", "Booking.h"
├── House.h          # Depends on <string>
├── Location.h       # Depends on <string>
├── MBomaHousingSystem.h  # Depends on <vector>, <string>, <map>, "User.h", "Location.h", "House.h", "Booking.h", "Payment.h"
├── Payment.h        # Depends on <string>, "User.h", "House.h"
├── User.h           # Depends on <string>
└── Utils.h          # Depends on <string>
```

This hierarchy shows how headers depend on each other. For instance, `MBomaHousingSystem.h` includes many other headers because it coordinates the entire system.

## Including Files

### Standard Library Headers

Including standard library headers:

```cpp
#include <string>    // String handling
#include <vector>    // Dynamic arrays
#include <iostream>  // Input/output streams
#include <limits>    // Numeric limits
#include <algorithm> // Algorithms like sort, find
#include <map>       // For std::map
```

### Project-Specific Headers

Including project headers:

```cpp
#include "include/House.h"
#include "include/User.h"
#include "include/DBConnector.h"
```

### Include Search Paths

The compiler looks for included files in specific directories:

1. **Angle brackets `<>`**: System directories (e.g., `/usr/include`)
2. **Quotes `""`**: Current directory first, then system directories

## Implementation Files

Implementation (`.cpp`) files contain the actual code for functions declared in headers:

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

// More implementations...
```

## The Compilation Process

C++ compilation involves several stages that transform source code into executable programs:

### 1. Preprocessing

The preprocessor handles directives like `#include`, `#define`, and `#ifdef`:

```cpp
// Before preprocessing
#include <iostream>
#define MAX_USERS 100

// After preprocessing (conceptual)
// Contents of iostream are inserted here
const int MAX_USERS = 100;
```

### 2. Compilation

The compiler translates preprocessed code into assembly language:

```cpp
// C++ code
int calculateTotal(int price, int quantity) {
    return price * quantity;
}

// Assembly-like output (simplified)
calculateTotal:
    mul rax, rdi, rsi
    ret
```

### 3. Assembly

The assembler converts assembly code into object files (machine code):

```
Object files (.o) contain:
- Machine code
- Symbol tables
- Relocation information
```

### 4. Linking

The linker combines object files and libraries into an executable:

```
Linking resolves:
- Function calls between different object files
- References to external libraries
- Symbol resolution
```

## Our Project's Build System

### Makefile Overview

The M-Boma Housing Project uses a Makefile to automate the build process:

```makefile
# From Makefile
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -I.
LDFLAGS = -lmysqlclient

# Source files directory
SRC_DIR = src

# Output directories
OBJ_DIR = obj
BIN_DIR = bin

# Source files
SRC = $(SRC_DIR)/main.cpp \
      $(SRC_DIR)/MBomaHousingSystem.cpp \
      $(SRC_DIR)/User.cpp \
      $(SRC_DIR)/Location.cpp \
      $(SRC_DIR)/House.cpp \
      $(SRC_DIR)/Booking.cpp \
      $(SRC_DIR)/Payment.cpp \
      $(SRC_DIR)/DBConnector.cpp \
      $(SRC_DIR)/Utils.cpp

# Object files
OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))

# Binary name
BIN = $(BIN_DIR)/mboma

# Default target
all: directories $(BIN)

# Create necessary directories
directories:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BIN_DIR)

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link object files into binary
$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(BIN) $(LDFLAGS)

# Clean compiled files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean directories
```

### Build Process

To build our project:

1. Create output directories: `obj/` and `bin/`
2. Compile each `.cpp` file to an `.o` object file
3. Link all object files into the final executable: `bin/mboma`

### Common Build Commands

```bash
# Build the entire project
make

# Clean compiled files
make clean

# Rebuild from scratch
make clean && make
```

## Common Header File Issues and Best Practices

### Circular Dependencies

Circular dependencies occur when header A includes header B, and header B includes header A:

```cpp
// HeaderA.h
#ifndef HEADER_A_H
#define HEADER_A_H
#include "HeaderB.h"  // Includes HeaderB.h
class A {
    B* b;  // References class B
};
#endif

// HeaderB.h
#ifndef HEADER_B_H
#define HEADER_B_H
#include "HeaderA.h"  // Includes HeaderA.h
class B {
    A* a;  // References class A
};
#endif
```

**Solution: Use forward declarations**

```cpp
// HeaderA.h
#ifndef HEADER_A_H
#define HEADER_A_H
class B;  // Forward declaration
class A {
    B* b;
};
#endif

// HeaderB.h
#ifndef HEADER_B_H
#define HEADER_B_H
class A;  // Forward declaration
class B {
    A* a;
};
#endif

// Implementation file includes both headers
// A.cpp
#include "HeaderA.h"
#include "HeaderB.h"
```

### Large Header Files

Excessive includes in headers can slow down compilation:

**Bad practice**:
```cpp
// MBomaHousingSystem.h (bad approach)
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <thread>
// Many unnecessary includes...
```

**Good practice**:
```cpp
// MBomaHousingSystem.h (good approach)
#include <vector>
#include <string>
#include <map>
// Only essential includes in header
// Implementation-specific includes go in .cpp file
```

### Namespace Pollution

Avoid using namespace in headers:

**Bad practice**:
```cpp
// Header file (bad)
#include <string>
using namespace std;  // Pollutes namespace for any file that includes this header

class House {
    string id;  // Now uses std::string
};
```

**Good practice**:
```cpp
// Header file (good)
#include <string>

class House {
    std::string id;  // Explicitly use std::string
};
```

## Modular Design with Headers

### Separation of Concerns

Our project separates functionality into distinct modules:

- **User Management**: `User.h/cpp`
- **Property Management**: `House.h/cpp`, `Location.h/cpp`
- **Booking System**: `Booking.h/cpp`, `Payment.h/cpp`
- **Database Connectivity**: `DBConnector.h/cpp`
- **Core System**: `MBomaHousingSystem.h/cpp`

This modular approach makes the code more maintainable and easier to understand.

### Interface vs. Implementation

Headers provide interfaces, while `.cpp` files provide implementations:

```cpp
// House.h - Interface
class House {
public:
    void book(const std::string& until);
    // Other methods...
};

// House.cpp - Implementation
void House::book(const std::string& until) {
    isAvailable = false;
    isBooked = true;
    bookedUntil = until;
}
```

This separation allows us to change implementations without affecting code that uses the interface.

## Database Configuration Example

Let's look at how our project uses a dedicated header file for database configuration:

```cpp
// From DBConfig.h
#ifndef DB_CONFIG_H
#define DB_CONFIG_H

#include <string>

namespace DBConfig {
    // Database connection settings
    const std::string DB_HOST = "localhost";
    const std::string DB_USER = "mboma_user";
    const std::string DB_PASS = "mboma_pass";
    const std::string DB_NAME = "mboma_housing";
    
    // Connection retry settings
    const int MAX_RETRY_ATTEMPTS = 3;
    const int RETRY_DELAY_MS = 1000;
}

#endif // DB_CONFIG_H
```

This approach keeps configuration constants separate from code logic, making them easy to find and modify.

## Practical Example: Header Organization

Let's examine a practical example of how headers are organized and used in the project:

1. **Main entry point**:

```cpp
// From main.cpp
#include "include/MBomaHousingSystem.h"
#include <iostream>

int main() {
    MBomaHousingSystem system;
    system.run();
    return 0;
}
```

2. **Core system header**:

```cpp
// From MBomaHousingSystem.h (simplified)
#ifndef MBOMA_HOUSING_SYSTEM_H
#define MBOMA_HOUSING_SYSTEM_H

#include <vector>
#include <string>
#include "User.h"
#include "Location.h"
#include "House.h"
#include "Booking.h"
#include "Payment.h"

// Forward declaration
class DBConnector;

class MBomaHousingSystem {
private:
    std::vector<User> users;
    std::vector<Location> locations;
    std::vector<House> houses;
    std::vector<Booking> bookings;
    std::vector<Payment> payments;
    
    DBConnector* dbConnector;
    bool useDatabase;
    
    int currentUserId;
    bool isLoggedIn;
    
    // Private methods...

public:
    MBomaHousingSystem();
    ~MBomaHousingSystem();
    void run();
};

#endif // MBOMA_HOUSING_SYSTEM_H
```

3. **Implementation file**:

```cpp
// From MBomaHousingSystem.cpp (simplified)
#include "include/MBomaHousingSystem.h"
#include "include/DBConnector.h"
#include "include/DBConfig.h"
#include "include/Utils.h"
#include <iostream>
#include <limits>
#include <algorithm>

MBomaHousingSystem::MBomaHousingSystem() 
    : dbConnector(nullptr), useDatabase(false), currentUserId(-1), isLoggedIn(false) {
    // Constructor implementation...
    dbConnector = new DBConnector();
    if (dbConnector->connect(DBConfig::DB_HOST, DBConfig::DB_USER, 
                           DBConfig::DB_PASS, DBConfig::DB_NAME)) {
        useDatabase = true;
        initializeData();
    } else {
        // Handle connection failure...
    }
}

MBomaHousingSystem::~MBomaHousingSystem() {
    if (dbConnector) {
        delete dbConnector;
    }
}

void MBomaHousingSystem::run() {
    // Implementation...
}

// Other method implementations...
```

This example shows:
1. How the main file includes only what it needs
2. How class declarations are separated from implementations
3. How implementation files include all necessary headers
4. How forward declarations reduce dependencies

## Exercise: Header File Organization

### Exercise 1: Create a Configuration Header
Create a `Config.h` file for application settings like:
- Maximum allowed bookings per user
- Default rental period in months
- Booking cancellation fee percentage

### Exercise 2: Resolve Circular Dependencies
Given two classes that reference each other, restructure the headers to avoid circular dependencies:
```cpp
// Original problematic code
// TownManager.h includes House.h
// House.h includes TownManager.h
```

### Exercise 3: Organize Project Headers
Design a header file structure for a new rental payment system with these components:
- Payment processor
- Receipt generator
- Transaction log
- Payment validation

## Summary

In this lesson, we've covered:
- The purpose and structure of header files
- How to prevent multiple inclusions with include guards
- Managing dependencies between headers
- The compilation process from preprocessing to linking
- Using a Makefile to automate building
- Best practices for header organization
- Common issues and how to avoid them

Understanding header files and the compilation process is essential for building modular, maintainable C++ applications. The M-Boma Housing Project demonstrates how proper organization of declarations and implementations leads to a more robust and flexible system.

## Further Reading
- [C++ Header Files - cppreference.com](https://en.cppreference.com/w/cpp/preprocessor/include)
- [The Compilation Process - cplusplus.com](http://www.cplusplus.com/doc/tutorial/introduction/)
- [Understanding Make - GNU Make Manual](https://www.gnu.org/software/make/manual/)
