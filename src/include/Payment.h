#ifndef PAYMENT_H
#define PAYMENT_H

#include <string>
#include "User.h"
#include "House.h"

/**
 * @brief Payment class to handle transactions
 */
class Payment {
private:
    int id;
    int bookingId;
    double amount;
    std::string paymentDate;
    std::string paymentMethod;
    std::string receiptNumber;

public:
    /**
     * @brief Constructor with parameters
     * @param id Payment identifier
     * @param bookingId Associated booking ID
     * @param amount Payment amount
     * @param paymentMethod Method of payment (e.g., "M-Pesa", "Bank Transfer")
     */
    Payment(int id, int bookingId, double amount, const std::string& paymentMethod);
    
    /**
     * @brief Generate and print receipt
     * @param user User who made the payment
     * @param house House that was paid for
     */
    void generateReceipt(const User& user, const House& house) const;
};

#endif // PAYMENT_H
