#include "request.hpp"

#include <stdexcept>

Request::Request(int id, int pickupFloor, int destinationFloor)
    : id_(id), pickupFloor_(pickupFloor), destinationFloor_(destinationFloor),
      direction_(destinationFloor > pickupFloor ? Direction::Up : Direction::Down) {
    if (id < 0 || pickupFloor < 0 || destinationFloor < 0 || pickupFloor == destinationFloor) {
        throw std::invalid_argument("Request must have valid, distinct non-negative floors");
    }
}

int Request::id() const noexcept { return id_; }
int Request::pickupFloor() const noexcept { return pickupFloor_; }
int Request::destinationFloor() const noexcept { return destinationFloor_; }
Direction Request::direction() const noexcept { return direction_; }
