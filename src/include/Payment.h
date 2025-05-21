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
    
    /**
     * @brief Set receipt number
     * @param receiptNum The receipt number to set
     */
    void setReceiptNumber(const std::string& receiptNum) {
        receiptNumber = receiptNum;
    }
    
    /**
     * @brief Get receipt number
     * @return The receipt number
     */
    std::string getReceiptNumber() const {
        return receiptNumber;
    }
};

#endif // PAYMENT_H
