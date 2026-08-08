#pragma once

#include "elevator.hpp"

#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

class ElevatorManager {
public:
    explicit ElevatorManager(int numberOfElevators);
    ElevatorManager(const ElevatorManager&) = delete;
    ElevatorManager& operator=(const ElevatorManager&) = delete;
    ~ElevatorManager();

    void submitRequest(std::shared_ptr<Request> request);

private:
    void assignElevators();
    Elevator& findNearestElevator(const Request& request);

    std::vector<std::unique_ptr<Elevator>> elevators_;
    std::vector<std::thread> elevatorThreads_;
    std::queue<std::shared_ptr<Request>> pendingRequests_;
    std::mutex queueMutex_;
    std::condition_variable requestAvailable_;
    bool stopping_{false};
    std::thread dispatcherThread_;
};
