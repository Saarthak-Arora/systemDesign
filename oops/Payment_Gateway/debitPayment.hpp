#ifndef DEBITPAYMENT_HPP
#define DEBITPAYMENT_HPP

#include "payment.hpp"

class debitPayment : public payment {
private:
    double amount;
    std::string cardNumber;
    std::string cardHolderName;
    std::string cvv;

public:
    debitPayment(double amount, const std::string& cardNumber, const std::string& cardHolderName, const std::string& cvv);
    void processPayment() override;
    void displayPaymentDetails() override;
};

#endif
