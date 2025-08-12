#ifndef PAYMENT_HPP
#define PAYMENT_HPP

#include <string>
#include <iostream>

class payment {
public:
    virtual ~payment() = default;
    virtual void processPayment() = 0;
    virtual void displayPaymentDetails() = 0;
};

#endif
