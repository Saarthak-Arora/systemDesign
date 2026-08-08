#pragma once

#include "request.hpp"

#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>

enum class MovingStatus { Moving, Stopped, Maintenance };

class Elevator {
public:
    Elevator(int id, int maxFloor = 10);
    Elevator(const Elevator&) = delete;
    Elevator& operator=(const Elevator&) = delete;

    void run();
    void stop();
    void addRequest(std::shared_ptr<Request> request);
    [[nodiscard]] int id() const noexcept;
    [[nodiscard]] int currentFloor() const noexcept;
    [[nodiscard]] MovingStatus status() const noexcept;

private:
    void moveToFloor(int floor);
    void changeDirection(Direction direction) noexcept;

    const int id_;
    const int maxFloor_;
    int currentFloor_{0};
    MovingStatus status_{MovingStatus::Stopped};
    Direction direction_{Direction::Idle};
    bool stopping_{false};
    std::queue<std::shared_ptr<Request>> requests_;
    mutable std::mutex mutex_;
    std::condition_variable requestAvailable_;
};
