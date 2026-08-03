#include "BookShow.hpp"
#include "BookingDetails.hpp"
#include "Room.hpp" 
#include "Seat.hpp"
#include "AmountDetail.hpp"
#include "Show.hpp" 
#include <iostream>
#include <thread>
#include <pthread.h>
#include "serviceAvailable.hpp"
#include "User.hpp"

unordered_map<string, BookingDetails*> bookings;

pair<string,double> BookShow::bookShow(BookingDetails* bd){
    lock_guard<mutex> lock(mtx);
    //cout<<"Booking for show: "<<bd->show->showName<<" from "<<bd->from<<" to "<<bd->to<<endl;
    cout<<this_thread::get_id()<<" is trying to book seats for user: "<<bd->user->name<<endl;
    for(auto& seatsinroom : bd->st){
        Room* room = seatsinroom->rm;
        for(auto& seat : seatsinroom->sts){
            if(!isSeatAvailable(bd->from, bd->to, room->roomNumber, seat->seatNumber)){
                return {"", 0.0};
            }
        }
    }
   string bookingId = "BKG" + to_string(bookings.size() + 1);
   this->booking_id = bookingId;
    bookings[bookingId] = bd;
    for(auto& seatsinroom : bd->st){
        Room* room = seatsinroom->rm;
        for(auto& seat : seatsinroom->sts){
            string fromto = bd->from + bd->to;
            seatAvailability[fromto][room->roomNumber][seat->seatNumber] = false; // Mark seat as unavailable
        }
    }
   bstatus = bookingStatus::RESEVERD;
   double totalPrice = 0.0;
   for(auto& seatsinroom : bd->st){
        for(auto& seat : seatsinroom->sts){
            totalPrice += getPrice(seat->getSeatType());
        }
    }
    totalPrice += bd->show->showPrice; // Add the show price to the total
    bd->totalPrice = totalPrice;
   return {bookingId, totalPrice};
}






