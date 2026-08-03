#include "serviceAvailable.hpp"
#include <iostream>
unordered_map<string, unordered_map<string,unordered_map<string, bool>>> seatAvailability; 
mutex mtx;

bool isSeatAvailable(string from, string to, string room_id, string seat_id){
    //lock_guard<mutex> lock(mtx);
    string fromto = from + to;
    std::cout<<this_thread::get_id()<<" is checking availability for seat: "<<seat_id<<" in room: "<<room_id<<" from: "<<from<<" to: "<<to<<endl;
    //cout<<"Checking availability for seat: "<<seat_id<<" in room: "<<room_id<<" from: "<<from<<" to: "<<to<<endl;
    if (seatAvailability.find(fromto) != seatAvailability.end() && 
        seatAvailability[fromto].find(room_id) != seatAvailability[fromto].end() && 
        seatAvailability[fromto][room_id].find(seat_id) != seatAvailability[fromto][room_id].end()) {
        return seatAvailability[fromto][room_id][seat_id];
    }
    return false;
}