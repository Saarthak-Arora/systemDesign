#include "RoomShowSeatManager.hpp"
#include "Show.hpp"
#include "Room.hpp"
#include "BookingDetails.hpp"
#include "Seat.hpp"
#include "serviceAvailable.hpp"


void RoomShowSeatManager::allocateRoomShow(Room* rm, Show* sh, string from, string to, tm d)
{
    RoomShow* rs = new RoomShow(rm, sh, from, to, d);
    roomShowAllocations.push_back(rs);
    findRooms[sh->show_id] = rs;
}

vector<seatsInRoom*> RoomShowSeatManager::getAllRoomWithAvailableSeatForShow(Show* sh)
{
    vector<seatsInRoom*> availableSeatsInRooms;
    if (findRooms.find(sh->show_id) != findRooms.end()) {
        RoomShow* rs = findRooms[sh->show_id];
        for(auto& seat : rs->room->seats){
            if(isSeatAvailable(rs->from, rs->to, rs->room->roomNumber, seat->seatNumber)){
                seatsInRoom* sir = new seatsInRoom();
                sir->rm = rs->room;
                sir->sts.push_back(seat.get());
                availableSeatsInRooms.push_back(sir);
            }

        }
    }
    return availableSeatsInRooms;
}

RoomShowSeatManager::~RoomShowSeatManager()
{
    for(auto& rs : roomShowAllocations){
        delete rs;
    }
}





