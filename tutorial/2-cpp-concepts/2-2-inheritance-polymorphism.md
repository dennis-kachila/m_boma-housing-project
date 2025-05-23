# Inheritance and Polymorphism in C++

## Introduction

Inheritance and polymorphism are fundamental concepts in object-oriented programming that allow for code reuse, extensibility, and flexible design. In the M-Boma Housing Project, these concepts could be applied to create a more sophisticated system where different types of properties can share common functionality while maintaining their unique characteristics.

This lesson explores inheritance and polymorphism concepts and demonstrates how they could enhance our housing management system.

## Inheritance Basics

Inheritance allows a class (derived/child class) to inherit properties and behaviors from another class (base/parent class).

### Base and Derived Classes

```cpp
// Basic Property class that could serve as a base class
class Property {
protected:
    std::string id;
    std::string address;
    double area;            // in square meters
    int locationId;         // Town ID
    bool isAvailable;
    
public:
    // Constructor
    Property(const std::string& id, const std::string& address, 
            double area, int locationId)
        : id(id), address(address), area(area), locationId(locationId),
          isAvailable(true) {}
    
    // Common methods for all properties
    std::string getId() const { return id; }
    std::string getAddress() const { return address; }
    double getArea() const { return area; }
    int getLocationId() const { return locationId; }
    bool getAvailability() const { return isAvailable; }
    void setAvailability(bool available) { isAvailable = available; }
    
    // Virtual method that might be overridden
    virtual double calculateValue() const {
        // Basic calculation based on area
        return area * 100000.0;  // Base rate per square meter
    }
    
    // Virtual destructor for proper cleanup in inheritance hierarchies
    virtual ~Property() {}
};

// Residential property for housing
class ResidentialProperty : public Property {
private:
    int bedrooms;
    int bathrooms;
    bool isFurnished;
    
public:
    ResidentialProperty(const std::string& id, const std::string& address,
                       double area, int locationId, int bedrooms, 
                       int bathrooms, bool isFurnished)
        : Property(id, address, area, locationId),
          bedrooms(bedrooms), bathrooms(bathrooms), 
          isFurnished(isFurnished) {}
    
    int getBedrooms() const { return bedrooms; }
    int getBathrooms() const { return bathrooms; }
    bool getFurnishedStatus() const { return isFurnished; }
    
    // Override the value calculation
    double calculateValue() const override {
        // Base value from parent class
        double baseValue = Property::calculateValue();
        
        // Adjustments based on residential features
        double bedroomFactor = 1.0 + (bedrooms * 0.1);  // 10% increase per bedroom
        double bathroomFactor = 1.0 + (bathrooms * 0.05);  // 5% increase per bathroom
        double furnishedBonus = isFurnished ? 1.1 : 1.0;  // 10% increase if furnished
        
        return baseValue * bedroomFactor * bathroomFactor * furnishedBonus;
    }
};

// Commercial property for business use
class CommercialProperty : public Property {
private:
    std::string zoning;      // e.g., "retail", "office", "industrial"
    bool hasParking;
    int floorNumber;
    
public:
    CommercialProperty(const std::string& id, const std::string& address,
                     double area, int locationId, const std::string& zoning,
                     bool hasParking, int floorNumber)
        : Property(id, address, area, locationId),
          zoning(zoning), hasParking(hasParking), floorNumber(floorNumber) {}
    
    std::string getZoning() const { return zoning; }
    bool getHasParking() const { return hasParking; }
    int getFloorNumber() const { return floorNumber; }
    
    // Override the value calculation
    double calculateValue() const override {
        // Base value from parent class
        double baseValue = Property::calculateValue();
        
        // Adjustments based on commercial features
        double zoningFactor = 1.0;
        if (zoning == "retail") zoningFactor = 1.2;
        else if (zoning == "office") zoningFactor = 1.1;
        else if (zoning == "industrial") zoningFactor = 0.9;
        
        double parkingBonus = hasParking ? 1.15 : 1.0;  // 15% increase with parking
        double floorFactor = 1.0 - (floorNumber * 0.02);  // 2% decrease per floor (ground floor is most valuable)
        if (floorFactor < 0.7) floorFactor = 0.7;  // Minimum 70% of base value
        
        return baseValue * zoningFactor * parkingBonus * floorFactor;
    }
};
```

In this example:
- `Property` is the base class with common attributes and behaviors
- `ResidentialProperty` and `CommercialProperty` are derived classes that inherit from `Property`
- Each derived class adds its own specific attributes and behaviors

### Inheritance Types

C++ supports three types of inheritance:

1. **Public inheritance**: Public members of the base class become public members of the derived class, and protected members of the base class become protected members of the derived class.

```cpp
class Apartment : public ResidentialProperty {
    // Public inheritance (most common)
};
```

2. **Protected inheritance**: Public and protected members of the base class become protected members of the derived class.

```cpp
class Apartment : protected ResidentialProperty {
    // Protected inheritance
};
```

3. **Private inheritance**: Public and protected members of the base class become private members of the derived class.

```cpp
class Apartment : private ResidentialProperty {
    // Private inheritance
};
```

### Access Specifiers in Inheritance

The accessibility of inherited members depends on both the access specifier in the base class and the type of inheritance:

| Base Class | Public Inheritance | Protected Inheritance | Private Inheritance |
|------------|-------------------|----------------------|---------------------|
| public     | public            | protected            | private             |
| protected  | protected         | protected            | private             |
| private    | inaccessible      | inaccessible         | inaccessible        |

## Multiple Inheritance

C++ allows a class to inherit from multiple base classes:

```cpp
// Interface for properties that can be booked
class Bookable {
protected:
    bool isBooked;
    std::string bookedUntil;
    
public:
    Bookable() : isBooked(false), bookedUntil("") {}
    
    bool getBookingStatus() const { return isBooked; }
    std::string getBookedUntil() const { return bookedUntil; }
    
    virtual void book(const std::string& until) {
        isBooked = true;
        bookedUntil = until;
    }
    
    virtual void unbook() {
        isBooked = false;
        bookedUntil = "";
    }
    
    virtual ~Bookable() {}
};

// Interface for properties that can be rated
class Ratable {
protected:
    double averageRating;
    int ratingCount;
    
public:
    Ratable() : averageRating(0.0), ratingCount(0) {}
    
    double getRating() const { return averageRating; }
    int getRatingCount() const { return ratingCount; }
    
    void addRating(double rating) {
        double totalRating = averageRating * ratingCount;
        ratingCount++;
        averageRating = (totalRating + rating) / ratingCount;
    }
    
    virtual ~Ratable() {}
};

// A vacation rental inherits from ResidentialProperty, Bookable, and Ratable
class VacationRental : public ResidentialProperty, public Bookable, public Ratable {
private:
    int minStayDays;
    bool hasWifi;
    
public:
    VacationRental(const std::string& id, const std::string& address,
                  double area, int locationId, int bedrooms, 
                  int bathrooms, bool isFurnished,
                  int minStayDays, bool hasWifi)
        : ResidentialProperty(id, address, area, locationId, bedrooms, bathrooms, isFurnished),
          Bookable(), Ratable(),
          minStayDays(minStayDays), hasWifi(hasWifi) {}
    
    int getMinStayDays() const { return minStayDays; }
    bool getHasWifi() const { return hasWifi; }
    
    // Override booking to check minimum stay
    void book(const std::string& until) override {
        // Calculate days between now and until...
        int stayDuration = 7;  // Placeholder for actual calculation
        
        if (stayDuration >= minStayDays) {
            Bookable::book(until);
            setAvailability(false);
        } else {
            throw std::invalid_argument("Booking duration below minimum stay requirement");
        }
    }
};
```

In this example, `VacationRental` inherits from three classes:
- `ResidentialProperty` for basic property features
- `Bookable` for booking functionality
- `Ratable` for user ratings

### The Diamond Problem

Multiple inheritance can lead to the "diamond problem" when a class inherits from two classes that both inherit from a common base class:

```
      BaseClass
      /       \
  Derived1   Derived2
      \       /
    JointDerived
```

This can lead to ambiguity about which version of inherited members to use. C++ resolves this with **virtual inheritance**:

```cpp
// Base class
class PropertyBase {
protected:
    std::string id;
    
public:
    PropertyBase(const std::string& id) : id(id) {}
    std::string getId() const { return id; }
};

// Two intermediate classes
class RentalProperty : public virtual PropertyBase {
protected:
    double rentalPrice;
    
public:
    RentalProperty(const std::string& id, double rentalPrice) 
        : PropertyBase(id), rentalPrice(rentalPrice) {}
    double getRentalPrice() const { return rentalPrice; }
};

class SaleProperty : public virtual PropertyBase {
protected:
    double salePrice;
    
public:
    SaleProperty(const std::string& id, double salePrice)
        : PropertyBase(id), salePrice(salePrice) {}
    double getSalePrice() const { return salePrice; }
};

// Joint derived class
class InvestmentProperty : public RentalProperty, public SaleProperty {
private:
    double returnOnInvestment;
    
public:
    InvestmentProperty(const std::string& id, double rentalPrice, double salePrice)
        : PropertyBase(id),  // Must initialize virtual base directly
          RentalProperty(id, rentalPrice),
          SaleProperty(id, salePrice),
          returnOnInvestment(rentalPrice * 12 / salePrice * 100) {}
    
    double getROI() const { return returnOnInvestment; }
};
```

The `virtual` keyword in `virtual PropertyBase` ensures only one instance of `PropertyBase` exists in the `InvestmentProperty` object.

## Polymorphism

Polymorphism allows objects of different classes to be treated as objects of a common base class, with behavior determined at runtime.

### Virtual Functions

Virtual functions enable runtime polymorphism:

```cpp
// Base class with virtual function
class Property {
public:
    virtual void displayDetails() const {
        std::cout << "Basic property details\n";
    }
    
    virtual double calculateRentalPrice() const = 0;  // Pure virtual function
};

// Derived classes implementing the virtual functions
class Apartment : public Property {
public:
    void displayDetails() const override {
        std::cout << "Apartment details\n";
    }
    
    double calculateRentalPrice() const override {
        return 15000.0;  // Base apartment price
    }
};

class Villa : public Property {
public:
    void displayDetails() const override {
        std::cout << "Villa details\n";
    }
    
    double calculateRentalPrice() const override {
        return 50000.0;  // Base villa price
    }
};
```

### Using Base Class Pointers

Polymorphism allows treating derived class objects through base class pointers:

```cpp
// Create derived objects
Apartment apt;
Villa villa;

// Store in base class pointers
Property* properties[] = { &apt, &villa };

// Polymorphic behavior
for (Property* prop : properties) {
    prop->displayDetails();  // Calls the appropriate version based on actual object type
    std::cout << "Rental price: " << prop->calculateRentalPrice() << std::endl;
}
```

### Pure Virtual Functions and Abstract Classes

A class with at least one pure virtual function is an abstract class:

```cpp
class PaymentProcessor {
public:
    // Pure virtual function (= 0)
    virtual bool processPayment(double amount, const std::string& currency) = 0;
    
    // Regular virtual function with default implementation
    virtual void validatePayment() {
        std::cout << "Basic payment validation\n";
    }
    
    // Regular function
    void recordTransaction(double amount) {
        std::cout << "Recording transaction of " << amount << std::endl;
    }
    
    // Virtual destructor for proper cleanup
    virtual ~PaymentProcessor() {}
};

// Cannot instantiate abstract classes:
// PaymentProcessor processor;  // Error!

// Must implement all pure virtual functions in derived classes
class CashPaymentProcessor : public PaymentProcessor {
public:
    bool processPayment(double amount, const std::string& currency) override {
        std::cout << "Processing cash payment of " << amount << " " << currency << std::endl;
        return true;
    }
};

class CreditCardPaymentProcessor : public PaymentProcessor {
private:
    std::string gatewayUrl;
    
public:
    CreditCardPaymentProcessor(const std::string& url) : gatewayUrl(url) {}
    
    bool processPayment(double amount, const std::string& currency) override {
        std::cout << "Processing credit card payment of " << amount << " " << currency;
        std::cout << " via " << gatewayUrl << std::endl;
        return true;
    }
    
    // Override the default implementation
    void validatePayment() override {
        std::cout << "Validating credit card payment with security checks\n";
    }
};
```

## Practical Application: Property Type Hierarchy

Let's design a more flexible property system for our housing project using inheritance and polymorphism:

```cpp
// Base Property class
class Property {
protected:
    std::string id;
    std::string address;
    double area;
    int locationId;
    bool isAvailable;
    double basePrice;
    
public:
    Property(const std::string& id, const std::string& address, 
            double area, int locationId, double basePrice)
        : id(id), address(address), area(area), 
          locationId(locationId), isAvailable(true), basePrice(basePrice) {}
    
    // Common methods
    std::string getId() const { return id; }
    std::string getAddress() const { return address; }
    double getArea() const { return area; }
    int getLocationId() const { return locationId; }
    bool isPropertyAvailable() const { return isAvailable; }
    void setAvailability(bool available) { isAvailable = available; }
    
    // Virtual methods that may be overridden
    virtual std::string getPropertyType() const = 0;
    virtual double getMonthlyRent() const = 0;
    virtual double getDepositFee() const = 0;
    
    // Virtual display method
    virtual void displayDetails() const {
        std::cout << "Property ID: " << id << std::endl;
        std::cout << "Type: " << getPropertyType() << std::endl;
        std::cout << "Address: " << address << std::endl;
        std::cout << "Area: " << area << " sq.m" << std::endl;
        std::cout << "Monthly Rent: KES " << getMonthlyRent() << std::endl;
        std::cout << "Deposit Required: KES " << getDepositFee() << std::endl;
        std::cout << "Status: " << (isAvailable ? "Available" : "Not Available") << std::endl;
    }
    
    virtual ~Property() {}
};

// Apartment class
class Apartment : public Property {
private:
    int floorNumber;
    int bedrooms;
    bool hasBalcony;
    
public:
    Apartment(const std::string& id, const std::string& address, 
             double area, int locationId, double basePrice,
             int floorNumber, int bedrooms, bool hasBalcony)
        : Property(id, address, area, locationId, basePrice),
          floorNumber(floorNumber), bedrooms(bedrooms), hasBalcony(hasBalcony) {}
    
    int getFloorNumber() const { return floorNumber; }
    int getBedrooms() const { return bedrooms; }
    bool getHasBalcony() const { return hasBalcony; }
    
    std::string getPropertyType() const override {
        return "Apartment";
    }
    
    double getMonthlyRent() const override {
        // Base price with adjustments for apartment features
        double price = basePrice;
        
        // Higher floors have higher rent
        price += (floorNumber - 1) * 1000;
        
        // More bedrooms mean higher rent
        price += bedrooms * 5000;
        
        // Balconies add value
        if (hasBalcony) {
            price += 2000;
        }
        
        return price;
    }
    
    double getDepositFee() const override {
        // Deposit is typically 2 months' rent
        return getMonthlyRent() * 2;
    }
    
    // Override to display apartment-specific details
    void displayDetails() const override {
        Property::displayDetails();  // Call base class method
        std::cout << "Floor: " << floorNumber << std::endl;
        std::cout << "Bedrooms: " << bedrooms << std::endl;
        std::cout << "Balcony: " << (hasBalcony ? "Yes" : "No") << std::endl;
    }
};

// Bungalow class
class Bungalow : public Property {
private:
    double landArea;
    bool hasGarden;
    bool hasGarage;
    
public:
    Bungalow(const std::string& id, const std::string& address, 
             double area, int locationId, double basePrice,
             double landArea, bool hasGarden, bool hasGarage)
        : Property(id, address, area, locationId, basePrice),
          landArea(landArea), hasGarden(hasGarden), hasGarage(hasGarage) {}
    
    double getLandArea() const { return landArea; }
    bool getHasGarden() const { return hasGarden; }
    bool getHasGarage() const { return hasGarage; }
    
    std::string getPropertyType() const override {
        return "Bungalow";
    }
    
    double getMonthlyRent() const override {
        // Base price with adjustments for bungalow features
        double price = basePrice;
        
        // Land area affects price
        price += landArea * 100;  // KES 100 per sq.m of land
        
        // Garden adds value
        if (hasGarden) {
            price += 5000;
        }
        
        // Garage adds value
        if (hasGarage) {
            price += 3000;
        }
        
        return price;
    }
    
    double getDepositFee() const override {
        // Deposit is typically 3 months' rent for bungalows
        return getMonthlyRent() * 3;
    }
    
    // Override to display bungalow-specific details
    void displayDetails() const override {
        Property::displayDetails();  // Call base class method
        std::cout << "Land Area: " << landArea << " sq.m" << std::endl;
        std::cout << "Garden: " << (hasGarden ? "Yes" : "No") << std::endl;
        std::cout << "Garage: " << (hasGarage ? "Yes" : "No") << std::endl;
    }
};
```

Using the property hierarchy in the housing system:

```cpp
// In MBomaHousingSystem class
class MBomaHousingSystem {
private:
    std::vector<std::unique_ptr<Property>> properties;
    // Other members...
    
public:
    void displayAvailableProperties(int locationId) {
        bool found = false;
        
        std::cout << "\n===== AVAILABLE PROPERTIES =====\n";
        for (const auto& property : properties) {
            if (property->getLocationId() == locationId && property->isPropertyAvailable()) {
                property->displayDetails();
                std::cout << "------------------------\n";
                found = true;
            }
        }
        
        if (!found) {
            std::cout << "No properties available in this location.\n";
        }
    }
    
    void addProperty(std::unique_ptr<Property> property) {
        properties.push_back(std::move(property));
    }
    
    // Other methods...
};

// Usage
MBomaHousingSystem system;

// Add different property types
system.addProperty(std::make_unique<Apartment>("A101", "123 Kahawa Rd", 75.5, 201, 15000, 3, 2, true));
system.addProperty(std::make_unique<Bungalow>("B201", "456 Runda Way", 120.0, 101, 30000, 500.0, true, true));

// Display properties - polymorphic behavior
system.displayAvailableProperties(201);  // Show Kahawa properties
```

## The "Override" Keyword (C++11)

The `override` keyword ensures a function is actually overriding a base class method:

```cpp
class BaseClass {
public:
    virtual void someFunction() { /* ... */ }
};

class DerivedClass : public BaseClass {
public:
    // Using override catches errors at compile time
    void someFunction() override { /* ... */ }
    
    // This would cause a compiler error if BaseClass had no virtualFunction
    // void virtualFunction() override { /* ... */ }
};
```

## The "Final" Keyword (C++11)

The `final` keyword prevents further overriding:

```cpp
class BaseClass {
public:
    virtual void someFunction() { /* ... */ }
};

class MiddleClass : public BaseClass {
public:
    // No further overriding allowed
    void someFunction() override final { /* ... */ }
};

class DerivedClass : public MiddleClass {
public:
    // Error: cannot override final function
    // void someFunction() override { /* ... */ }
};
```

## Practical Example: Payment Processing System

Let's implement a payment processing system using inheritance and polymorphism:

```cpp
// Base payment processor
class PaymentProcessor {
protected:
    std::string paymentMethod;
    bool successful;
    std::string receiptNumber;
    
public:
    PaymentProcessor(const std::string& method) 
        : paymentMethod(method), successful(false), receiptNumber("") {}
    
    virtual bool processPayment(double amount, int bookingId) = 0;
    
    bool isSuccessful() const { return successful; }
    std::string getReceiptNumber() const { return receiptNumber; }
    std::string getPaymentMethod() const { return paymentMethod; }
    
    virtual void displayReceipt(const User& user, const House& house, 
                             double amount, const std::string& date) const {
        std::cout << "\n======= M-BOMA PAYMENT RECEIPT =======\n";
        std::cout << "Receipt Number: " << receiptNumber << std::endl;
        std::cout << "Date: " << date << std::endl;
        std::cout << "Customer: " << user.getName() << std::endl;
        std::cout << "Property: " << house.getId() << " - " << house.getType() << std::endl;
        std::cout << "Amount: KES " << amount << std::endl;
        std::cout << "Payment Method: " << paymentMethod << std::endl;
        std::cout << "Status: " << (successful ? "Successful" : "Failed") << std::endl;
    }
    
    virtual ~PaymentProcessor() {}
};

// Cash payment implementation
class CashPaymentProcessor : public PaymentProcessor {
private:
    std::string cashierName;
    
public:
    CashPaymentProcessor(const std::string& cashier) 
        : PaymentProcessor("Cash"), cashierName(cashier) {}
    
    bool processPayment(double amount, int bookingId) override {
        // Simulate cash payment processing
        std::cout << "Processing cash payment of KES " << amount << "...\n";
        
        // Generate receipt number
        receiptNumber = "CASH-" + std::to_string(bookingId) + "-" + 
                       std::to_string(std::time(nullptr));
        
        successful = true;
        std::cout << "Cash payment successful. Receipt number: " << receiptNumber << std::endl;
        return successful;
    }
    
    void displayReceipt(const User& user, const House& house, 
                      double amount, const std::string& date) const override {
        // Call base class implementation
        PaymentProcessor::displayReceipt(user, house, amount, date);
        
        // Add cash-specific details
        std::cout << "Cashier: " << cashierName << std::endl;
        std::cout << "Paid in full via cash.\n";
    }
};

// Mobile money payment implementation
class MobilePaymentProcessor : public PaymentProcessor {
private:
    std::string mobileProvider;
    std::string transactionId;
    
public:
    MobilePaymentProcessor(const std::string& provider) 
        : PaymentProcessor("Mobile Money"), mobileProvider(provider), transactionId("") {}
    
    bool processPayment(double amount, int bookingId) override {
        // Simulate mobile payment processing
        std::cout << "Processing " << mobileProvider << " payment of KES " << amount << "...\n";
        std::cout << "Enter transaction ID: ";
        std::getline(std::cin, transactionId);
        
        if (transactionId.length() < 5) {
            std::cout << "Invalid transaction ID.\n";
            successful = false;
            return successful;
        }
        
        // Generate receipt number
        receiptNumber = mobileProvider + "-" + std::to_string(bookingId) + "-" + 
                       transactionId.substr(0, 4);
        
        successful = true;
        std::cout << mobileProvider << " payment successful. Receipt number: " << receiptNumber << std::endl;
        return successful;
    }
    
    void displayReceipt(const User& user, const House& house, 
                      double amount, const std::string& date) const override {
        // Call base class implementation
        PaymentProcessor::displayReceipt(user, house, amount, date);
        
        // Add mobile-specific details
        std::cout << "Provider: " << mobileProvider << std::endl;
        std::cout << "Transaction ID: " << transactionId << std::endl;
    }
};

// Credit card payment implementation
class CardPaymentProcessor : public PaymentProcessor {
private:
    std::string cardType;
    std::string lastFourDigits;
    
public:
    CardPaymentProcessor(const std::string& type) 
        : PaymentProcessor("Credit/Debit Card"), cardType(type), lastFourDigits("") {}
    
    bool processPayment(double amount, int bookingId) override {
        // Simulate card payment processing
        std::cout << "Processing " << cardType << " payment of KES " << amount << "...\n";
        std::cout << "Enter last four digits of card: ";
        std::getline(std::cin, lastFourDigits);
        
        if (lastFourDigits.length() != 4 || !std::all_of(lastFourDigits.begin(), 
                                                       lastFourDigits.end(), ::isdigit)) {
            std::cout << "Invalid card number format.\n";
            successful = false;
            return successful;
        }
        
        // Generate receipt number
        receiptNumber = "CARD-" + std::to_string(bookingId) + "-" + lastFourDigits;
        
        successful = true;
        std::cout << cardType << " payment successful. Receipt number: " << receiptNumber << std::endl;
        return successful;
    }
    
    void displayReceipt(const User& user, const House& house, 
                      double amount, const std::string& date) const override {
        // Call base class implementation
        PaymentProcessor::displayReceipt(user, house, amount, date);
        
        // Add card-specific details
        std::cout << "Card Type: " << cardType << std::endl;
        std::cout << "Card Number: **** **** **** " << lastFourDigits << std::endl;
    }
};
```

Using the payment system in the housing application:

```cpp
// In MBomaHousingSystem class
void MBomaHousingSystem::processPayment(int bookingId, double amount) {
    // Find the booking
    Booking* booking = findBookingById(bookingId);
    if (!booking) {
        std::cout << "Booking not found.\n";
        return;
    }
    
    // Find associated user and house
    User* user = findUserById(booking->getUserId());
    House* house = findHouse(booking->getHouseId());
    
    if (!user || !house) {
        std::cout << "User or house details not found.\n";
        return;
    }
    
    // Show payment options
    std::cout << "\n===== PAYMENT OPTIONS =====\n";
    std::cout << "1. Cash\n";
    std::cout << "2. M-Pesa\n";
    std::cout << "3. Credit/Debit Card\n";
    std::cout << "Enter payment method (1-3): ";
    
    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    // Create appropriate payment processor using polymorphism
    std::unique_ptr<PaymentProcessor> processor;
    
    switch (choice) {
        case 1:
            processor = std::make_unique<CashPaymentProcessor>("John Doe");
            break;
        case 2:
            processor = std::make_unique<MobilePaymentProcessor>("M-Pesa");
            break;
        case 3:
            processor = std::make_unique<CardPaymentProcessor>("Visa");
            break;
        default:
            std::cout << "Invalid payment method.\n";
            return;
    }
    
    // Process payment polymorphically
    if (processor->processPayment(amount, bookingId)) {
        // Create payment record
        Payment payment(getNextId("payment"), bookingId, amount, processor->getPaymentMethod());
        payment.setReceiptNumber(processor->getReceiptNumber());
        payments.push_back(payment);
        
        // Update booking status
        booking->markAsPaid();
        
        // Display receipt
        std::string date = getCurrentDateTime();
        processor->displayReceipt(*user, *house, amount, date);
    } else {
        std::cout << "Payment failed. Please try again.\n";
    }
}
```

## Exercise: Inheritance and Polymorphism

### Exercise 1: Extend Property Types
Extend the property hierarchy with a new property type:

```cpp
class Studio : public Property {
    // TODO: Implement a studio apartment class
    // with appropriate attributes and overridden methods
};
```

### Exercise 2: Payment Processing
Add a new payment method to the payment processing system:

```cpp
class BankTransferPaymentProcessor : public PaymentProcessor {
    // TODO: Implement bank transfer payment processing
    // with appropriate attributes and overridden methods
};
```

### Exercise 3: Property Reporting
Create a reporting system that can work with different property types:

```cpp
class PropertyReport {
public:
    // TODO: Create methods that use polymorphism to generate reports
    // about different types of properties
    void generateOccupancyReport(const std::vector<std::unique_ptr<Property>>& properties);
    void generateRevenueReport(const std::vector<std::unique_ptr<Property>>& properties);
};
```

## Summary

In this lesson, we've covered:
- Inheritance as a mechanism for code reuse and specialization
- Creating base and derived classes with common and specialized behaviors
- Access control in inheritance (public, protected, private)
- Multiple inheritance and the diamond problem
- Polymorphism through virtual functions
- Abstract classes and pure virtual functions
- Practical applications of inheritance and polymorphism in a housing management system
- Modern C++ features like `override` and `final`

Inheritance and polymorphism provide powerful tools for creating flexible, extensible software designs. In the M-Boma Housing Project, these concepts can be applied to model different property types, payment methods, and other entities with shared behaviors but specialized implementations.

## Further Reading
- [C++ Inheritance - cppreference.com](https://en.cppreference.com/w/cpp/language/derived_class)
- [Virtual Functions and Polymorphism - cplusplus.com](http://www.cplusplus.com/doc/tutorial/polymorphism/)
- [Multiple Inheritance - isocpp.org](https://isocpp.org/wiki/faq/multiple-inheritance)
