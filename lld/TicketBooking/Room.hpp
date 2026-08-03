#pragma once
#include <string>
#include <vector>
#include <memory>
#include <utility>
using namespace std;

class Seat;

class Room {
    public:
        const string roomNumber;
        int capacity;
        vector<unique_ptr<Seat>> seats;
        Room(string roomNumber) : roomNumber(roomNumber){
        }
        void addSeat(unique_ptr<Seat> seat) {
            seats.push_back(std::move(seat));
            capacity++;
        }
        // Room* const operator=(const Room& other) {
        //     if (this != &other) {
        //         // Copy the room number and capacity
        //         const_cast<string&>(roomNumber) = other.roomNumber;
        //         const_cast<int&>(capacity) = other.capacity;

        //         // Deep copy the seats
        //         seats.clear();
        //         for (const auto& seat : other.seats) {
        //             seats.push_back(make_unique<Seat>(*seat));
        //         }
        //     }
        //     return this;
        // }
};