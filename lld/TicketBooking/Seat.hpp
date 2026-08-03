#pragma once
#include <string>
using namespace std;

enum class SeatType {
    Economy,
    Business,
    FirstClass
};

enum class AvailabilityStatus {
    Available,
    Reserved,
    Occupied
};


class Seat{
    public:
        const string s_id;
        const string seatNumber;
        SeatType type;  
        AvailabilityStatus status;
        const string roomNumber;
        double price;
        Seat(string s_id, string seatNumber, SeatType type) : s_id(s_id), seatNumber(seatNumber), type(type), status(AvailabilityStatus::Available) {}

        string getSeatNumber() const {
            return seatNumber;
        }

        SeatType getSeatType() const {
            return type;
        }

        AvailabilityStatus getAvailabilityStatus() const {
            return status;
        }

        void reserveSeat() {
            if (status == AvailabilityStatus::Available) {
                status = AvailabilityStatus::Reserved;
            }
        }

        void occupySeat() {
            if (status == AvailabilityStatus::Reserved) {
                status = AvailabilityStatus::Occupied;
            }
        }

        void releaseSeat() {
            if (status == AvailabilityStatus::Reserved || status == AvailabilityStatus::Occupied) {
                status = AvailabilityStatus::Available;
            }
        }

        void setSeatPrice(double price) {
            this->price = price;
        }

        double getSeatPrice() const {
            return price;
        }

};