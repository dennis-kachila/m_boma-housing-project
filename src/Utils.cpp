#include "include/Utils.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

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
