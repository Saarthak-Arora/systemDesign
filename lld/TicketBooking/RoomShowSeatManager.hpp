#pragma once
#include <string>
#include <vector>
#include <ctime>
#include <unordered_map>
using namespace std;


class Show;
class Room;
class Seat;
class BookingDetails;
class RoomShow;
class seatsInRoom;


class RoomShow
{
    public:
    Room* room;
    Show* show;
    string from;
    string to;
    tm date; 
    RoomShow(Room* room, Show* show, string from, string to, tm date) : room(room), show(show), from(from), to(to), date(date) {}

};


class RoomShowSeatManager
{
private:
   
public:
    vector<RoomShow*> roomShowAllocations;
    RoomShowSeatManager(/* args */){};
    ~RoomShowSeatManager();
    void allocateRoomShow(Room* rm, Show* sh, string from, string to, tm d);
    unordered_map<string, RoomShow*> findRooms; 
    vector<seatsInRoom*> getAllRoomWithAvailableSeatForShow(Show* sh);
};

