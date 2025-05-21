#include "include/User.h"
#include <iostream>

User::User() : isLoggedIn(false) {}

User::User(const std::string& name, const std::string& phone, 
           const std::string& email, const std::string& password)
    : name(name), phone(phone), email(email), password(password), isLoggedIn(false) {}

bool User::registerUser() {
    std::cout << "\n===== USER REGISTRATION =====\n";
    
    std::cout << "Enter your name: ";
    std::getline(std::cin, name);
    
    std::cout << "Enter your phone number: ";
    std::getline(std::cin, phone);
    
    std::cout << "Enter your email: ";
    std::getline(std::cin, email);
    
    std::cout << "Enter your password: ";
    std::getline(std::cin, password);
    
    std::cout << "\nRegistration successful!\n";
    return true;
}

bool User::login(const std::string& inputEmail, const std::string& inputPassword) {
    if (email == inputEmail && password == inputPassword) {
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

std::string User::getPhone() const {
    return phone;
}
