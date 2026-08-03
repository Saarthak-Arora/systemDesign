#include "AmountDetail.hpp"

unordered_map<SeatType, double> seatTypePrice = {
    {SeatType::Economy, 10.0},
    {SeatType::Business, 20.0},
    {SeatType::FirstClass, 30.0}
};

double getPrice(SeatType type) {
    if (seatTypePrice.find(type) != seatTypePrice.end()) {
        return seatTypePrice[type];
    }
    return 0.0; // Default price if type not found
}

double getTotalPrice(const vector<Seat*>& seats,const double showPrice) {
    double totalPrice = 0.0;
    for (const auto& seat : seats) {
        totalPrice += getPrice(seat->getSeatType());
    }
    totalPrice += showPrice; // Add the show price to the total
    return totalPrice;
}