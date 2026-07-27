#pragma once

#include "User.hpp"
#include "Vehicle.hpp"
#include "Message.hpp"

#include <mutex>
#include <string>
#include <vector>

class Trip;

enum class DriverStatus { Available, OnTrip, Offline };

class Driver final : public User {
public:
    Driver(std::string name, std::string email, std::string mobileNumber, std::string licenseNumber,
           Vehicle vehicle, Location location);

    [[nodiscard]] const std::string& licenseNumber() const noexcept;
    [[nodiscard]] const Vehicle& vehicle() const noexcept;
    [[nodiscard]] DriverStatus status() const noexcept;
    void setStatus(DriverStatus status) noexcept;

    Message acceptRideCall(Trip& trip);
    void receiveRideCall(const std::string& tripId);
    void removeRideCall(const std::string& tripId);
    [[nodiscard]] std::vector<std::string> pendingRideCalls() const;

private:
    std::string licenseNumber_;
    Vehicle vehicle_;
    DriverStatus status_{DriverStatus::Available};
    mutable std::mutex mutex_;
    std::vector<std::string> rideCalls_;
};
