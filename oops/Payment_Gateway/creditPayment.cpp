#include "payment.hpp"

class creditPayment : public payment {
private:
    double amount;
    std::string cardNumber;
    std::string cardHolderName;
    std::string cvv;
public:
    creditPayment(double amount, const std::string& cardNumber, const std::string& cardHolderName, const std::string& cvv)
        : amount(amount), cardNumber(cardNumber), cardHolderName(cardHolderName), cvv(cvv) {}

    void processPayment() override{
        std::cout << "Processing credit payment of using card number: " << cardNumber << std::endl;
    }

    void displayPaymentDetails() override{
        std::cout << "Credit Payment Details:" << std::endl;
        std::cout << "Amount: " << amount << std::endl;
        std::cout << "Card Number: " << cardNumber << std::endl;
        std::cout << "Card Holder Name: " << cardHolderName << std::endl;
    }
};