#include "include/Booking.h"
#include "include/Utils.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

Booking::Booking(int id, int userId, int houseId)
    : id(id), userId(userId), houseId(houseId), isPaid(false) {
    
    bookingDate = getCurrentDateTime();
    
    // Calculate expiry date (30 days from now)
    auto now = std::chrono::system_clock::now();
    auto expiry = now + std::chrono::hours(24 * 30);
    std::time_t expiry_time = std::chrono::system_clock::to_time_t(expiry);
    
    std::stringstream ss;
    ss << std::put_time(std::localtime(&expiry_time), "%Y-%m-%d %H:%M:%S");
    expiryDate = ss.str();
}

int Booking::getId() const {
    return id;
}

int Booking::getUserId() const {
    return userId;
}

int Booking::getHouseId() const {
    return houseId;
}

std::string Booking::getBookingDate() const {
    return bookingDate;
}

std::string Booking::getExpiryDate() const {
    return expiryDate;
}

bool Booking::getPaymentStatus() const {
    return isPaid;
}

void Booking::markAsPaid() {
    isPaid = true;
}
