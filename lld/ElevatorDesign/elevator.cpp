#include "elevator.hpp"

#include <chrono>
#include <iostream>
#include <stdexcept>
#include <thread>

Elevator::Elevator(int id, int maxFloor) : id_(id), maxFloor_(maxFloor) {
    if (id < 0 || maxFloor <= 0) throw std::invalid_argument("Invalid elevator configuration");
}

void Elevator::run() {
    while (true) {
        std::shared_ptr<Request> request;
        {
            std::unique_lock<std::mutex> lock(mutex_);
            requestAvailable_.wait(lock, [this] { return stopping_ || !requests_.empty(); });
            if (stopping_ && requests_.empty()) return;
            request = std::move(requests_.front());
            requests_.pop();
        }
        moveToFloor(request->pickupFloor());
        moveToFloor(request->destinationFloor());
        std::cout << "Elevator " << id_ << " completed request " << request->id() << '\n';
    }
}

void Elevator::stop() {
    { std::lock_guard<std::mutex> lock(mutex_); stopping_ = true; }
    requestAvailable_.notify_all();
}

void Elevator::addRequest(std::shared_ptr<Request> request) {
    if (!request) throw std::invalid_argument("Request cannot be null");
    { std::lock_guard<std::mutex> lock(mutex_); if (stopping_) throw std::logic_error("Elevator is stopping"); requests_.push(std::move(request)); }
    requestAvailable_.notify_one();
}

int Elevator::id() const noexcept { return id_; }
int Elevator::currentFloor() const noexcept { std::lock_guard<std::mutex> lock(mutex_); return currentFloor_; }
MovingStatus Elevator::status() const noexcept { std::lock_guard<std::mutex> lock(mutex_); return status_; }

void Elevator::moveToFloor(int floor) {
    if (floor < 0 || floor > maxFloor_) throw std::out_of_range("Requested floor is outside elevator range");
    while (true) {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            if (currentFloor_ == floor) { status_ = MovingStatus::Stopped; direction_ = Direction::Idle; return; }
            status_ = MovingStatus::Moving;
            changeDirection(floor > currentFloor_ ? Direction::Up : Direction::Down);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::lock_guard<std::mutex> lock(mutex_);
        currentFloor_ += direction_ == Direction::Up ? 1 : -1;
    }
}

void Elevator::changeDirection(Direction direction) noexcept { direction_ = direction; }
