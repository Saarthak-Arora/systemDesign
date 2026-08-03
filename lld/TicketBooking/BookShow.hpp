#pragma once
#include <string>
#include <mutex>
#include "RoomShowSeatManager.hpp"

using namespace std;

class BookingDetails;

extern
unordered_map<string, BookingDetails*> bookings;

enum class bookingStatus {
    NOTINITIATED,
    RESEVERD,
    Confirmed,
    Cancelled
};

enum class paymentStatus {
    PENDING,
    SUCCESS,
    FAILED
};

class BookShow {
    public:
        mutex mtx;
        string booking_id;
        bookingStatus bstatus = bookingStatus::NOTINITIATED;
        BookShow(){};
        pair<string,double> bookShow(BookingDetails* bd);
        bool releaseBooking(string booking_id);
};