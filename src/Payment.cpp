#include "include/Payment.h"
#include "include/Utils.h"
#include <iostream>
#include <iomanip>
#include <fstream>

Payment::Payment(int id, int bookingId, double amount, const std::string& paymentMethod)
    : id(id), bookingId(bookingId), amount(amount), paymentMethod(paymentMethod) {
    
    paymentDate = getCurrentDateTime();
    receiptNumber = generateReceiptNumber();
}

void Payment::generateReceipt(const User& user, const House& house) const {
    std::cout << "\n========== PAYMENT RECEIPT ==========\n";
    std::cout << "Receipt Number: " << receiptNumber << "\n";
    std::cout << "Date: " << paymentDate << "\n";
    std::cout << "Customer: " << user.getName() << "\n";
    std::cout << "Phone: " << user.getPhone() << "\n";
    std::cout << "Email: " << user.getEmail() << "\n";
    std::cout << "Property: " << house.getType() << " at " << house.getAddress() << "\n";
    std::cout << "Amount Paid: KES " << std::fixed << std::setprecision(2) << amount << "\n";
    std::cout << "Payment Method: " << paymentMethod << "\n";
    std::cout << "Status: PAID\n";
    std::cout << "======================================\n";
    
    // Save receipt to file
    std::ofstream receiptFile(receiptNumber + ".txt");
    if (receiptFile.is_open()) {
        receiptFile << "========== PAYMENT RECEIPT ==========\n";
        receiptFile << "Receipt Number: " << receiptNumber << "\n";
        receiptFile << "Date: " << paymentDate << "\n";
        receiptFile << "Customer: " << user.getName() << "\n";
        receiptFile << "Phone: " << user.getPhone() << "\n";
        receiptFile << "Email: " << user.getEmail() << "\n";
        receiptFile << "Property: " << house.getType() << " at " << house.getAddress() << "\n";
        receiptFile << "Amount Paid: KES " << std::fixed << std::setprecision(2) << amount << "\n";
        receiptFile << "Payment Method: " << paymentMethod << "\n";
        receiptFile << "Status: PAID\n";
        receiptFile << "======================================\n";
        receiptFile.close();
        std::cout << "Receipt saved to " << receiptNumber << ".txt\n";
    }
}
