#include "Driver.hpp"

#include "Trip.hpp"

#include <algorithm>
#include <stdexcept>
#include <utility>

Driver::Driver(std::string name, std::string email, std::string mobileNumber, std::string licenseNumber,
               Vehicle vehicle, Location location)
    : User(std::move(name), std::move(email), std::move(mobileNumber), std::move(location)),
      licenseNumber_(std::move(licenseNumber)), vehicle_(std::move(vehicle)) {
    if (licenseNumber_.empty() || !vehicle_.isRegistered()) {
        throw std::invalid_argument("Driver license and registered vehicle are required");
    }
}

const std::string& Driver::licenseNumber() const noexcept { return licenseNumber_; }
const Vehicle& Driver::vehicle() const noexcept { return vehicle_; }
DriverStatus Driver::status() const noexcept { std::lock_guard<std::mutex> lock(mutex_); return status_; }
void Driver::setStatus(DriverStatus status) noexcept { std::lock_guard<std::mutex> lock(mutex_); status_ = status; }

Message Driver::acceptRideCall(Trip& trip) {
    Message result = trip.acceptByDriver(*this);
    if (result.success) {
        removeRideCall(trip.id());
    }
    return result;
}

void Driver::receiveRideCall(const std::string& tripId) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (std::find(rideCalls_.begin(), rideCalls_.end(), tripId) == rideCalls_.end()) rideCalls_.push_back(tripId);
}

void Driver::removeRideCall(const std::string& tripId) {
    std::lock_guard<std::mutex> lock(mutex_);
    rideCalls_.erase(std::remove(rideCalls_.begin(), rideCalls_.end(), tripId), rideCalls_.end());
}

std::vector<std::string> Driver::pendingRideCalls() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return rideCalls_;
}
