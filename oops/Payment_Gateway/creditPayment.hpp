#ifndef CREDITPAYMENT_HPP
#define CREDITPAYMENT_HPP

#include "payment.hpp"

class creditPayment : public payment {
private:
    double amount;
    std::string cardNumber;
    std::string cardHolderName;
    std::string cvv;

public:
    creditPayment(double amount, const std::string& cardNumber, const std::string& cardHolderName, const std::string& cvv);
    void processPayment() override;
    void displayPaymentDetails() override;
};

#endif
