#include <bits/stdc++.h>
#include <iostream>
#include "payment.hpp"
#include "debitPayment.cpp"
#include "creditPayment.cpp"
using namespace std;

int main(){
    
    payment* usingDebitCard =  new debitPayment(1000, "1234", "kk", "123");
    usingDebitCard->processPayment();
    usingDebitCard->displayPaymentDetails();

    payment* usingCreditCard = new creditPayment(2000, "4321", "kk", "456");
    usingCreditCard->processPayment();
    usingCreditCard->displayPaymentDetails();



    return 0;
}