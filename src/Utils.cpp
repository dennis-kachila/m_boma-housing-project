#include "include/Utils.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <functional> // for std::hash
#include <openssl/sha.h>

std::string getCurrentDateTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    
    std::stringstream ss;
    ss << std::put_time(std::localtime(&now_time), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

std::string generateReceiptNumber() {
    static int receiptCounter = 1000;
    receiptCounter++;
    
    std::stringstream ss;
    ss << "RCP" << receiptCounter;
    return ss.str();
}

std::string hashPassword(const std::string& password) {
    // Using SHA-256 for password hashing
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password.c_str(), password.size());
    SHA256_Final(hash, &sha256);
    
    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    
    return ss.str();
}

bool verifyPassword(const std::string& password, const std::string& hashedPassword) {
    return hashPassword(password) == hashedPassword;
}

bool equalsIgnoreCase(const std::string& str1, const std::string& str2) {
    if (str1.size() != str2.size()) {
        return false;
    }
    
    for (size_t i = 0; i < str1.size(); ++i) {
        if (tolower(str1[i]) != tolower(str2[i])) {
            return false;
        }
    }
    
    return true;
}
