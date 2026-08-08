#pragma once

enum class Direction { Up, Down, Idle };

class Request {
public:
    Request(int id, int pickupFloor, int destinationFloor);

    int id() const noexcept;
    int pickupFloor() const noexcept;
    int destinationFloor() const noexcept;
    Direction direction() const noexcept;

private:
    int id_;
    int pickupFloor_;
    int destinationFloor_;
    Direction direction_;
};
