#include "include/House.h"

House::House(int id, const std::string& type, double depositFee, double monthlyRent,
      int locationId, const std::string& address, const std::string& mapLink)
    : id(id), type(type), depositFee(depositFee), monthlyRent(monthlyRent),
      locationId(locationId), address(address), mapLink(mapLink),
      isAvailable(true), isBooked(false), bookedUntil("") {}

int House::getId() const {
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
}

void House::book(const std::string& until) {
    isBooked = true;
    bookedUntil = until;
}

void House::unbook() {
    isBooked = false;
    bookedUntil = "";
}
