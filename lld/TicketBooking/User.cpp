#include "User.hpp"
#include "BookShow.hpp"

 bool User::bookForShow(BookingDetails* bd){
    BookShow* booking = new BookShow();
    if (booking->bookShow(bd).first == "") {
        return false;
    }
    bookings.push_back(booking->booking_id);
    return true;
 }