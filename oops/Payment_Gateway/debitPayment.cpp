
#include "payment.hpp"
#include <string>

class debitPayment : public payment {
public:
    double amount;
    std::string cardNumber;
    std::string cardHolderName;
    std::string cvv;
public:
    debitPayment(double amount, const std::string& cardNumber, const std::string& cardHolderName, const std::string& cvv)
        : amount(amount), cardNumber(cardNumber), cardHolderName(cardHolderName), cvv(cvv) {}

    void processPayment() override {

        std::cout << "Processing debit payment of " << amount << " using card number: " << cardNumber << std::endl;
    }

    void displayPaymentDetails() override {
        std::cout << "Debit Payment Details:" << std::endl;
        std::cout << "Amount: " << amount << std::endl;
        std::cout << "Card Number: " << cardNumber << std::endl;
        std::cout << "Card Holder Name: " << cardHolderName << std::endl;
    }
};