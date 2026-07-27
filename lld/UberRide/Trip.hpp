#pragma once

#include "CalculateAmountService.hpp"
#include "Location.hpp"
#include "Message.hpp"

#include <chrono>
#include <mutex>
#include <string>
#include <vector>

class Customer;
class Driver;

enum class TripStatus { Requested, Accepted, InProgress, Completed, Cancelled };

class Trip {
public:
    Trip(const Customer& customer, Location pickup, Location destination, RideType rideType);

    [[nodiscard]] const std::string& id() const noexcept;
    [[nodiscard]] const std::string& customerId() const noexcept;
    [[nodiscard]] TripStatus status() const noexcept;
    [[nodiscard]] double distanceKm() const noexcept;
    [[nodiscard]] double quotedAmount() const noexcept;
    [[nodiscard]] const Location& pickup() const noexcept;
    [[nodiscard]] const Location& destination() const noexcept;
    [[nodiscard]] std::vector<Driver*> notifiedDrivers() const;

    void notifyDrivers(const std::vector<Driver*>& drivers);
    Message acceptByDriver(Driver& driver);
    Message start();
    Message complete();
    Message cancel();

private:
    void removePendingCallsLocked();

    std::string id_;
    std::string customerId_;
    Location pickup_;
    Location destination_;
    RideType rideType_;
    double distanceKm_;
    double quotedAmount_;
    TripStatus status_{TripStatus::Requested};
    Driver* assignedDriver_{nullptr};
    std::vector<Driver*> notifiedDrivers_;
    std::chrono::system_clock::time_point bookingTime_{std::chrono::system_clock::now()};
    std::chrono::system_clock::time_point startTime_{};
    std::chrono::system_clock::time_point endTime_{};
    mutable std::mutex mutex_;
};
