#include <string>
#include <vector>
#include <ctime>
#include <iostream>
#include "User.hpp"
#include "BookingDetails.hpp"
#include "Show.hpp"
#include "Room.hpp"
#include "Seat.hpp"
#include "RoomShowSeatManager.hpp"
#include "BookShow.hpp"
#include "AmountDetail.hpp"
#include "serviceAvailable.hpp"
#include <pthread.h>
#include <thread>
using namespace std;

int main(){
    User* u1 = new User("u1","sa","sagmail","1234567890");
    User* u2 = new User("u2","ra","ragmail","0987654321");
    User* u3 = new User("u3","pa","pagmail","1122334455");
    User* u4 = new User("u4","ka","kagmail","5566778899");
    User* u5 = new User("u5","ma","magmail","6677889900");

    Seat* s1 = new Seat("s1","S1",SeatType::Economy);
    Seat* s2 = new Seat("s2","S2",SeatType::Business);
    Seat* s3 = new Seat("s3","S3",SeatType::FirstClass);
    Seat* s4 = new Seat("s4","S4",SeatType::Economy);
    Seat* s5 = new Seat("s5","S5",SeatType::Business);
    Seat* s6 = new Seat("s6","S6",SeatType::FirstClass);
    Seat* s7 = new Seat("s7","S7",SeatType::Economy);
    Seat* s8 = new Seat("s8","S8",SeatType::Business);
    Seat* s9 = new Seat("s9","S9",SeatType::FirstClass);
    Seat* s10 = new Seat("s10","S10",SeatType::Economy);
    Seat* s11 = new Seat("s11","S11",SeatType::Business);
    Seat* s12 = new Seat("s12","S12",SeatType::FirstClass);
    Seat* s13 = new Seat("s13","S13",SeatType::Economy);
    Seat* s14 = new Seat("s14","S14",SeatType::Business);
    Seat* s15 = new Seat("s15","S15",SeatType::FirstClass);
    Seat* s16 = new Seat("s16","S16",SeatType::Economy);
    Seat* s17 = new Seat("s17","S17",SeatType::Business);

    Room* r1 = new Room("R1");
    r1->addSeat(unique_ptr<Seat>(s1));
    r1->addSeat(unique_ptr<Seat>(s2));
    r1->addSeat(unique_ptr<Seat>(s3));

    Room* r2 = new Room("R2");
    r2->addSeat(unique_ptr<Seat>(s4));
    r2->addSeat(unique_ptr<Seat>(s5));
    r2->addSeat(unique_ptr<Seat>(s6));

    Room* r3 = new Room("R3");
    r3->addSeat(unique_ptr<Seat>(s7));
    r3->addSeat(unique_ptr<Seat>(s8));

    Room* r4 = new Room("R4");
    r4->addSeat(unique_ptr<Seat>(s9));
    r4->addSeat(unique_ptr<Seat>(s10));

    Room* r5 = new Room("R5");
    r5->addSeat(unique_ptr<Seat>(s11));
    r5->addSeat(unique_ptr<Seat>(s12));
    r5->addSeat(unique_ptr<Seat>(s13));
    r5->addSeat(unique_ptr<Seat>(s14));
    r5->addSeat(unique_ptr<Seat>(s15));
    r5->addSeat(unique_ptr<Seat>(s16));
    r5->addSeat(unique_ptr<Seat>(s17));

    Show* sh1 = new Show("SH1","Show 1",50.0);
    Show* sh2 = new Show("SH2","Show 2",75.0);
    Show* sh3 = new Show("SH3","Show 3",100.0);

    RoomShowSeatManager* manager = new RoomShowSeatManager();
    manager->allocateRoomShow(r1, sh1, "10:00", "12:00", {});
    manager->allocateRoomShow(r2, sh1, "10:00", "12:00", {});
    manager->allocateRoomShow(r3, sh2, "13:00", "15:00", {});
    manager->allocateRoomShow(r4, sh2, "13:00", "15:00", {});
    manager->allocateRoomShow(r5, sh3, "16:00", "18:00", {});
    manager->allocateRoomShow(r1, sh3, "16:00", "18:00", {});
    manager->allocateRoomShow(r2, sh3, "16:00", "18:00", {});
    manager->allocateRoomShow(r3, sh1, "10:00", "12:00", {});
    manager->allocateRoomShow(r4, sh1, "10:00", "12:00", {});
    manager->allocateRoomShow(r5, sh2, "13:00", "15:00", {});
    manager->allocateRoomShow(r1, sh2, "13:00", "15:00", {});

    seatAvailability["10:0012:00"]["R1"]["S1"] = true;
    seatAvailability["10:0012:00"]["R1"]["S2"] = true;
    seatAvailability["10:0012:00"]["R1"]["S3"] = true;
    seatAvailability["10:0012:00"]["R2"]["S4"] = true;
    seatAvailability["10:0012:00"]["R2"]["S5"] = true;
    seatAvailability["10:0012:00"]["R2"]["S6"] = true;
    seatAvailability["13:0015:00"]["R3"]["S7"] = true;
    seatAvailability["13:0015:00"]["R3"]["S8"] = true;
    seatAvailability["13:0015:00"]["R4"]["S9"] = true;
    seatAvailability["13:0015:00"]["R4"]["S10"] = true;
    seatAvailability["16:0018:00"]["R5"]["S11"] = true;
    seatAvailability["16:0018:00"]["R5"]["S12"] = true;
    seatAvailability["16:0018:00"]["R5"]["S13"] = true;
    seatAvailability["16:0018:00"]["R5"]["S14"] = true;
    seatAvailability["16:0018:00"]["R5"]["S15"] = true;
    seatAvailability["16:0018:00"]["R5"]["S16"] = true;
    seatAvailability["16:0018:00"]["R5"]["S17"] = true;
    seatAvailability["16:0018:00"]["R1"]["S1"] = true;
    seatAvailability["16:0018:00"]["R1"]["S2"] = true;


    /*

    print the detail of availble room

    manager->getAllRoomWithAvailableSeatForShow(sh1);
    manager->getAllRoomWithAvailableSeatForShow(sh2);
    manager->getAllRoomWithAvailableSeatForShow(sh3);

    */

   // for demo perpuse book the same seat for two differnet user
    vector<seatsInRoom*> avaibleSeat;
    seatsInRoom* sir1 = new seatsInRoom();
    sir1->rm = r1;
    sir1->sts.push_back(s1);
    sir1->sts.push_back(s2);
    avaibleSeat.push_back(sir1);

    vector<seatsInRoom*> avaibleSeat2;
    seatsInRoom* sir2 = new seatsInRoom();
    sir2->rm = r3;
    sir2->sts.push_back(s7);
    sir2->sts.push_back(s8);
    avaibleSeat2.push_back(sir2);   


    BookShow* booking = new BookShow();
    BookingDetails* bd1 = new BookingDetails(sh1, avaibleSeat, u1, "10:00", "12:00", {});
    pair<string,double> p = booking->bookShow(bd1);
    if(p.first != ""){
        cout << "Booking successful. Booking ID: " << p.first << ", Total Price: " << p.second << endl;
    } else {
        cout << "Booking failed." << endl;
    }

    BookingDetails* bd2 = new BookingDetails(sh2, avaibleSeat2, u2, "13:00", "15:00", {});
    BookingDetails* bd3 = new BookingDetails(sh2, avaibleSeat2, u3, "13:00", "15:00", {});
    BookingDetails* bd4 = new BookingDetails(sh2, manager->getAllRoomWithAvailableSeatForShow(sh2), u3, "16:00", "18:00", {});

    thread t1([&](){
        pair<string,double> p2 = booking->bookShow(bd2);
        if(p2.first != ""){
            cout << "Bookceing successful. Booking ID: " << p2.first << ", Total Price: " << p2.second << endl;
        } else {
            cout << "Booking failed for user"<< bd2->user->name<< endl;
        }
    });

    thread t2([&](){
        pair<string,double> p3 = booking->bookShow(bd3);
        if(p3.first != ""){
            cout << "Booking successful. Booking ID: " << p3.first << ", Total Price: " << p3.second << endl;
        } else {
            cout << "Booking failed for user"<< bd3->user->name<< endl;
        }
    });

    // thread t3([&](){
    //     pair<string,double> p4 = booking->bookShow(bd4);
    //     if(p4.first != ""){
    //         cout << "Booking successful. Booking ID: " << p4.first << ", Total Price: " << p4.second << endl;
    //     } else {
    //         cout << "Booking failed for user"<< bd4->user<< endl;
    //     }
    // });

    t1.join();
    t2.join();
    // t3.join(); 

    return 0;
}


//  TicketBooking % clang++ -g -O0 -std=c++17 \
//   AmountDetail.cpp BookShow.cpp RoomShowSeatManager.cpp \
//   serviceAvailable.cpp User.cpp main.cpp \
//   -o ticket_booking

//   need to do improvement as

//   [P1] Synchronize availability reads with booking writes — [serviceAvailable.cpp (line 11)](/Users/saarthakarora/Documents/System_design/lld/TicketBooking/serviceAvailable.cpp:11)
// BookShow::bookShow() locks mtx before writing seatAvailability, but RoomShowSeatManager::getAllRoomWithAvailableSeatForShow() calls isSeatAvailable() without that lock. A UI/search thread reading availability while a booking thread updates the same unordered_map creates a data race and undefined behavior. Protect both read and write paths with the same lock—preferably a per-room-show shared_mutex.
// [P1] Preserve every room allocation for a show — [RoomShowSeatManager.cpp (line 13)](/Users/saarthakarora/Documents/System_design/lld/TicketBooking/RoomShowSeatManager.cpp:13)
// findRooms[sh->show_id] = rs overwrites the prior room each time you allocate another room for the same show. For example, SH1 is allocated to several rooms in main.cpp, but only the final allocation remains discoverable. Store a vector<RoomShow*> per show ID, or key each allocation by a unique room-show-time identifier.
// [P2] Use room-show-level locking instead of one global mutex — [BookShow.cpp (line 16)](/Users/saarthakarora/Documents/System_design/lld/TicketBooking/BookShow.cpp:16)
// The shared global mtx correctly prevents duplicate bookings, but it serializes bookings for every room and show. A booking for Room R1 blocks an independent booking for R3. Put a mutex on each room-show inventory and lock only the inventory/inventories requested by that booking. Lock multiple inventories in a stable order for multi-room bookings.
// [P2] Include the booking date in the availability key — [BookShow.cpp (line 33)](/Users/saarthakarora/Documents/System_design/lld/TicketBooking/BookShow.cpp:33)
// The key is only from + to, even though BookingDetails includes a date. Booking seat S1 in R1 from 10:00–12:00 on one date marks it unavailable for the same time on every other date. Include date and a separator-safe identifier in the inventory key.
// [P2] Initialize room capacity before incrementing it — [Room.hpp (line 13)](/Users/saarthakarora/Documents/System_design/lld/TicketBooking/Room.hpp:13)
// capacity has no initial value, then addSeat() increments it. Reading/incrementing an uninitialized integer is undefined behavior. Initialize it with int capacity{0};.
// [P3] Keep strict builds warning-free — [main.cpp (line 22)](/Users/saarthakarora/Documents/System_design/lld/TicketBooking/main.cpp:22)
// A strict build with -Werror fails because u4, u5, and bd4 are created but unused. The normal build runs and correctly allows only one of the two competing bookings, but CI-style strict builds fail.