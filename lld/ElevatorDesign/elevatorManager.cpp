#include "elevatorManager.hpp"

#include <algorithm>
#include <cstdlib>
#include <stdexcept>
#include <utility>

ElevatorManager::ElevatorManager(int numberOfElevators) {
    if (numberOfElevators <= 0) throw std::invalid_argument("At least one elevator is required");
    elevators_.reserve(numberOfElevators);
    elevatorThreads_.reserve(numberOfElevators);
    for (int id = 0; id < numberOfElevators; ++id) {
        elevators_.push_back(std::make_unique<Elevator>(id));
        elevatorThreads_.emplace_back(&Elevator::run, elevators_.back().get());
    }
    dispatcherThread_ = std::thread(&ElevatorManager::assignElevators, this);
}

ElevatorManager::~ElevatorManager() {
    { std::lock_guard<std::mutex> lock(queueMutex_); stopping_ = true; }
    requestAvailable_.notify_all();
    if (dispatcherThread_.joinable()) dispatcherThread_.join();
    for (const auto& elevator : elevators_) elevator->stop();
    for (std::thread& thread : elevatorThreads_) if (thread.joinable()) thread.join();
}

void ElevatorManager::submitRequest(std::shared_ptr<Request> request) {
    if (!request) throw std::invalid_argument("Request cannot be null");
    { std::lock_guard<std::mutex> lock(queueMutex_); if (stopping_) throw std::logic_error("Elevator manager is stopping"); pendingRequests_.push(std::move(request)); }
    requestAvailable_.notify_one();
}

void ElevatorManager::assignElevators() {
    while (true) {
        std::shared_ptr<Request> request;
        {
            std::unique_lock<std::mutex> lock(queueMutex_);
            requestAvailable_.wait(lock, [this] { return stopping_ || !pendingRequests_.empty(); });
            if (stopping_ && pendingRequests_.empty()) return;
            request = std::move(pendingRequests_.front());
            pendingRequests_.pop();
        }
        findNearestElevator(*request).addRequest(std::move(request));
    }
}

Elevator& ElevatorManager::findNearestElevator(const Request& request) {
    auto nearest = std::min_element(elevators_.begin(), elevators_.end(), [&request](const auto& left, const auto& right) {
        return std::abs(left->currentFloor() - request.pickupFloor()) < std::abs(right->currentFloor() - request.pickupFloor());
    });
    return **nearest;
}
