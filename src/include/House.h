#ifndef HOUSE_H
#define HOUSE_H

#include <string>

/**
 * @brief House class to represent available houses
 */
class House {
private:
    int id;
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
     * @param id House identifier
     * @param type House type
     * @param depositFee Deposit amount
     * @param monthlyRent Monthly rent amount
     * @param locationId Town ID where house is located
     * @param address House address
     * @param mapLink Google Maps link
     */
    House(int id, const std::string& type, double depositFee, double monthlyRent,
          int locationId, const std::string& address, const std::string& mapLink);
    
    /**
     * @brief Get house ID
     * @return House ID
     */
    int getId() const;
    
    /**
     * @brief Get house type
     * @return House type (e.g. "Apartment", "Bungalow")
     */
    std::string getType() const;
    
    /**
     * @brief Get deposit fee
     * @return Deposit amount
     */
    double getDepositFee() const;
    
    /**
     * @brief Get monthly rent
     * @return Monthly rent amount
     */
    double getMonthlyRent() const;
    
    /**
     * @brief Get location ID
     * @return Town ID where house is located
     */
    int getLocationId() const;
    
    /**
     * @brief Get house address
     * @return House address
     */
    std::string getAddress() const;
    
    /**
     * @brief Get map link
     * @return Google Maps link
     */
    std::string getMapLink() const;
    
    /**
     * @brief Check house availability
     * @return true if house is available
     */
    bool getAvailability() const;
    
    /**
     * @brief Check booking status
     * @return true if house is booked
     */
    bool getBookingStatus() const;
    
    /**
     * @brief Get booking expiry date
     * @return Booking expiry date
     */
    std::string getBookedUntil() const;
    
    /**
     * @brief Set house availability
     * @param available New availability status
     */
    void setAvailability(bool available);
    
    /**
     * @brief Book the house until a specified date
     * @param until Booking expiry date
     */
    void book(const std::string& until);
    
    /**
     * @brief Remove booking from house
     */
    void unbook();
};

#endif // HOUSE_H
