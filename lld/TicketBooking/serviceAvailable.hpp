#ifndef SERVICEAVAILABLE_HPP
#define SERVICEAVAILABLE_HPP
#include <string>
#include <unordered_map>
#include <mutex>
using namespace std;

extern
unordered_map<string, unordered_map<string,unordered_map<string, bool>>> seatAvailability; // time -> room -> seat -> availability

extern mutex mtx;

bool isSeatAvailable(string from, string to, string roomno, string seat_id);

#endif 