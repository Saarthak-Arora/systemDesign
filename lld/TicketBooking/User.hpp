#pragma once
#include <string>
#include <vector>
using namespace std;

class BookingDetails;

class User{
    public:
        const string user_id;
        const string name;
        const string email;
        const string phoneNumber;
        vector<string> bookings;
        User(string user_id, string name, string email, string phoneNumber) : user_id(user_id), name(name), email(email), phoneNumber(phoneNumber) {}
        bool bookForShow(BookingDetails* bd);
};