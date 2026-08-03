#pragma once
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class User;
class Seat;
class Room;
class Show;


class seatsInRoom{
public:
    Room* rm;
    vector<Seat*> sts;
};

class BookingDetails {
    public:
        Show* show;
        vector<seatsInRoom*> st;
        User* user;
        const string from;
        const string to;
        tm date;
        double totalPrice = 0.0;

        BookingDetails(Show* show, vector<seatsInRoom*> st, User* user, string from, string to, tm date) : show(show), st(st), user(user), from(from), to(to), date(date) {}
};

