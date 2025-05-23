# Control Structures in C++

## Introduction

Control structures manage the flow of execution in C++ programs. They allow us to make decisions, repeat operations, and branch to different parts of code based on conditions. In the M-Boma Housing Project, control structures are used extensively for user interaction, data validation, and business logic implementation.

This lesson explores how control structures are implemented in our project, from simple conditionals to complex menu navigation.

## Conditional Statements

Conditional statements allow the program to execute different code blocks based on specified conditions.

### if-else Statements

The `if-else` statement is the most basic form of conditional execution:

```cpp
// From User.cpp - Password validation during registration
if (plainPassword == confirmPassword) {
    passwordsMatch = true;
    password = hashPassword(plainPassword); // Store the hashed password
} else {
    std::cout << "Passwords do not match. Please try again.\n";
}
```

Complex conditions can be chained using `else if`:

```cpp
// From MBomaHousingSystem.cpp - User menu navigation
if (choice == 1) {
    // Browse houses
    browseCatalogue();
} else if (choice == 2) {
    // Search houses
    searchHouses();
} else if (choice == 3) {
    // View bookings
    viewBookings();
} else if (choice == 4) {
    // Logout
    logout();
} else if (choice == 5) {
    // Exit system
    running = false;
} else {
    std::cout << "Invalid choice. Please try again.\n";
}
```

### Nested Conditionals

Sometimes we need to check conditions within other conditions:

```cpp
// From MBomaHousingSystem.cpp - Booking validation
if (isLoggedIn) {
    if (findHouse(houseId)) {
        if (house->getAvailability()) {
            // Process booking
            processBooking(house);
        } else {
            std::cout << "Sorry, this house is not available for booking.\n";
        }
    } else {
        std::cout << "House not found.\n";
    }
} else {
    std::cout << "You must be logged in to book a house.\n";
}
```

## Looping Constructs

Loops execute a block of code repeatedly while a condition is true or for a specific number of iterations.

### while Loops

The `while` loop continues execution as long as its condition remains true:

```cpp
// From MBomaHousingSystem.cpp - Main application loop
bool running = true;
while (running) {
    displayMainMenu();
    int choice = getUserChoice();
    
    // Process user choice
    if (choice == EXIT_OPTION) {
        running = false;
    } else {
        processUserChoice(choice);
    }
}
```

### do-while Loops

The `do-while` loop ensures the code block executes at least once before checking the condition:

```cpp
// From User.cpp - Password validation
std::string plainPassword;
std::string confirmPassword;
bool passwordsMatch = false;

do {
    std::cout << "Enter your password: ";
    std::getline(std::cin, plainPassword);
    
    std::cout << "Confirm your password: ";
    std::getline(std::cin, confirmPassword);
    
    if (plainPassword == confirmPassword) {
        passwordsMatch = true;
    } else {
        std::cout << "Passwords do not match. Please try again.\n";
    }
} while (!passwordsMatch);
```

### for Loops

The `for` loop is ideal when the number of iterations is known or when iterating over collections:

```cpp
// From MBomaHousingSystem.cpp - Displaying available counties
std::cout << "\n===== COUNTIES =====\n";
for (const auto& location : locations) {
    if (location.getType() == "county") {
        std::cout << location.getId() << ". " << location.getName() << "\n";
    }
}
```

### Range-based for Loops

Modern C++ (C++11 and later) provides an easier syntax for iterating over collections:

```cpp
// Displaying all houses in a town
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
```

## Switch Statements

The `switch` statement provides a more elegant way to handle multiple conditions based on a single variable:

```cpp
// From MBomaHousingSystem.cpp - Main menu handling
switch (choice) {
    case 1: {
        // Register new user
        User newUser;
        if (newUser.registerUser()) {
            users.push_back(newUser);
            currentUserId = users.size();
            isLoggedIn = true;
            std::cout << "You are now logged in!\n";
        }
        break;
    }
    case 2: {
        // Login existing user
        loginUser();
        break;
    }
    case 3:
        // Exit application
        running = false;
        break;
    default:
        std::cout << "Invalid choice. Please try again.\n";
        break;
}
```

### Switch Statement Best Practices

1. Always include a `default` case to handle unexpected values
2. Use braces `{}` when declaring variables within a case 
3. Remember to include `break` statements to prevent fall-through
4. Consider using `enum` for related constants instead of magic numbers

```cpp
// Better approach with enum
enum MainMenuOption {
    REGISTER = 1,
    LOGIN,
    EXIT
};

switch (choice) {
    case REGISTER:
        // Handle registration
        break;
    case LOGIN:
        // Handle login
        break;
    case EXIT:
        // Handle exit
        break;
    default:
        // Handle invalid choice
        break;
}
```

## Break and Continue Statements

### Break Statement

The `break` statement exits the current loop or switch statement:

```cpp
// From MBomaHousingSystem.cpp - Finding a user by email
User* MBomaHousingSystem::findUserByEmail(const std::string& email) {
    for (auto& user : users) {
        if (user.getEmail() == email) {
            return &user; // Found the user, break the loop and return
        }
    }
    return nullptr; // Not found
}
```

### Continue Statement

The `continue` statement skips the rest of the current iteration and proceeds to the next:

```cpp
// Displaying only available houses
for (const auto& house : houses) {
    if (!house.getAvailability()) {
        continue; // Skip unavailable houses
    }
    
    // Display house details
    std::cout << house.getId() << ". " << house.getType() << " - KES " 
              << house.getMonthlyRent() << "/month\n";
}
```

## Nested Loops

Complex operations sometimes require loops within loops:

```cpp
// From MBomaHousingSystem.cpp - Finding houses by multiple criteria
for (const auto& county : counties) {
    std::cout << "County: " << county.getName() << "\n";
    
    for (const auto& town : towns) {
        if (town.getParentId() == county.getId()) {
            std::cout << "  Town: " << town.getName() << "\n";
            
            for (const auto& house : houses) {
                if (house.getLocationId() == town.getId() && 
                    house.getAvailability()) {
                    // Display available house in this town
                    std::cout << "    House: " << house.getType() 
                              << " (" << house.getId() << ")\n";
                }
            }
        }
    }
}
```

## Practical Example: Menu Navigation

In the M-Boma Housing Project, control structures form the backbone of the menu-based user interface. Here's how a typical navigation flow is implemented:

```cpp
void MBomaHousingSystem::browseCatalogue() {
    bool browsing = true;
    while (browsing) {
        displayCounties();
        std::cout << "\n0. Back to Main Menu\n";
        std::cout << "Enter county number (or 0 to go back): ";
        
        int countyId;
        std::cin >> countyId;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        if (countyId == 0) {
            browsing = false;
        } else {
            bool validCounty = false;
            for (const auto& location : locations) {
                if (location.getType() == "county" && location.getId() == countyId) {
                    validCounty = true;
                    break;
                }
            }
            
            if (validCounty) {
                browseTownsInCounty(countyId);
            } else {
                std::cout << "Invalid county ID. Please try again.\n";
                waitForEnter();
            }
        }
    }
}
```

This code demonstrates several control structures working together:
1. `while` loop for the main browsing session
2. `if-else` for handling the back option
3. `for` loop with `break` for validating county ID
4. Nested control structures for multi-level navigation

## Exercise: Control Flow Implementation

### Exercise 1: Menu System
Implement a simplified version of the housing system menu with the following options:
1. List all houses
2. Search by house type
3. Search by price range
4. Exit

Use appropriate control structures to handle user navigation.

### Exercise 2: Input Validation
Write a function that validates user input for a house ID using the following requirements:
- Must be exactly 4 characters
- First character must be a letter
- Last three characters must be alphanumeric
- Return true if valid, false otherwise

### Exercise 3: Filtering Houses
Implement a function that:
1. Takes a vector of houses, minimum price, and maximum price
2. Returns a new vector containing only houses within the price range
3. Uses appropriate looping and conditional statements

## Summary

In this lesson, we've explored:
- Conditional execution with `if-else` statements
- Different types of loops: `while`, `do-while`, `for`, and range-based `for`
- The `switch` statement for multi-branching logic
- `break` and `continue` statements for loop control
- Combining control structures for complex program flow

Control structures form the decision-making backbone of our M-Boma Housing Project, enabling dynamic user interaction, data filtering, and business logic implementation. Understanding these structures is essential for creating responsive and user-friendly applications.

## Further Reading
- [C++ Control Structures - cppreference.com](https://en.cppreference.com/w/cpp/language/statements)
- [C++ Loops - cplusplus.com](http://www.cplusplus.com/doc/tutorial/control/)
- [Switch Statements Best Practices - isocpp.org](https://isocpp.org/wiki/faq/statements#switches)
