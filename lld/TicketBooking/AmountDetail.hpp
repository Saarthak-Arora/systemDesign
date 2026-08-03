#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "Seat.hpp"
using namespace std;

extern unordered_map<SeatType, double> seatTypePrice;

double getPrice(SeatType type);

double getTotalPrice(const vector<Seat*>& seats, double showPrice);


