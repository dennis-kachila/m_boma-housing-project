#include "include/User.h"
#include "include/Utils.h"
#include <iostream>
#include <limits>

User::User() : isLoggedIn(false) {}

User::User(const std::string& name, const std::string& phone, 
           const std::string& email, const std::string& password)
    : name(name), phone(phone), email(email), 
      password(hashPassword(password)), isLoggedIn(false) {}

bool User::registerUser() {
    std::cout << "\n===== USER REGISTRATION =====\n";
    
    std::cout << "Enter your name: ";
    std::getline(std::cin, name);
    
    std::cout << "Enter your phone number: ";
    std::getline(std::cin, phone);
    
    std::cout << "Enter your email: ";
    std::getline(std::cin, email);
    
    std::string plainPassword;
    std::string confirmPassword;
    bool passwordsMatch = false;
    
    while (!passwordsMatch) {
        std::cout << "Enter your password: ";
        std::getline(std::cin, plainPassword);
        
        std::cout << "Confirm your password: ";
        std::getline(std::cin, confirmPassword);
        
        if (plainPassword == confirmPassword) {
            passwordsMatch = true;
            password = hashPassword(plainPassword); // Store the hashed password
        } else {
            std::cout << "Passwords do not match. Please try again.\n";
        }
    }
    
    std::cout << "\nRegistration successful!\n";
    return true;
}

bool User::login(const std::string& inputEmail, const std::string& inputPassword) {
    if (equalsIgnoreCase(email, inputEmail) && verifyPassword(inputPassword, password)) {
        isLoggedIn = true;
        return true;
    }
    return false;
}

void User::logout() {
    isLoggedIn = false;
}

bool User::isAuthenticated() const {
    return isLoggedIn;
}

std::string User::getName() const {
    return name;
}

std::string User::getEmail() const {
    return email;
}

std::string User::getPassword() const {
    return password;
}

std::string User::getPhone() const {
    return phone;
}

void User::setName(const std::string& name) {
    this->name = name;
}

void User::setEmail(const std::string& email) {
    this->email = email;
}

void User::setPhone(const std::string& phone) {
    this->phone = phone;
}

void User::setPasswordHash(const std::string& hashedPassword) {
    this->password = hashedPassword;
}
