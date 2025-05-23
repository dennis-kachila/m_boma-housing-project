#ifndef BOOKING_H
#define BOOKING_H

#include <string>

/**
 * @brief Booking class to handle house reservations
 */
class Booking {
private:
    int id;
    int userId;
    std::string houseId;
    std::string bookingDate;
    std::string expiryDate;
    bool isPaid;

public:
    /**
     * @brief Constructor with parameters
     * @param id Booking identifier
     * @param userId User identifier
     * @param houseId House identifier
     */
    Booking(int id, int userId, const std::string& houseId);
    
    /**
     * @brief Get booking ID
     * @return Booking ID
     */
    int getId() const;
    
    /**
     * @brief Set booking ID
     * @param newId New booking identifier (typically from database)
     */
    void setId(int newId);
    
    /**
     * @brief Get user ID
     * @return User ID of booking owner
     */
    int getUserId() const;
    
    /**
     * @brief Get house ID
     * @return House ID that is booked
     */
    std::string getHouseId() const;
    
    /**
     * @brief Get booking date
     * @return Date when booking was made
     */
    std::string getBookingDate() const;
    
    /**
     * @brief Set booking date
     * @param date New booking date (typically from database)
     */
    void setBookingDate(const std::string& date);
    
    /**
     * @brief Get expiry date
     * @return Date when booking expires
     */
    std::string getExpiryDate() const;
    
    /**
     * @brief Set expiry date
     * @param date New expiry date (typically from database)
     */
    void setExpiryDate(const std::string& date);
    
    /**
     * @brief Get payment status
     * @return true if booking has been paid for
     */
    bool getPaymentStatus() const;
    
    /**
     * @brief Mark booking as paid
     */
    void markAsPaid();
};

#endif // BOOKING_H
