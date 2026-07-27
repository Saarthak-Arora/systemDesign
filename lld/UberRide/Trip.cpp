#include "Trip.hpp"

#include "Customer.hpp"
#include "Driver.hpp"

#include <algorithm>
#include <atomic>
#include <stdexcept>
#include <utility>

namespace {
std::atomic<unsigned long long> nextTripId{1};
Message failure(std::string text) { return {false, std::move(text)}; }
}

Trip::Trip(const Customer& customer, Location pickup, Location destination, RideType rideType)
    : id_("trip-" + std::to_string(nextTripId.fetch_add(1))), customerId_(customer.id()), pickup_(std::move(pickup)),
      destination_(std::move(destination)), rideType_(rideType), distanceKm_(pickup_.distanceToKm(destination_)),
      quotedAmount_(calculateAmount(rideType_, distanceKm_)) {}

const std::string& Trip::id() const noexcept { return id_; }
const std::string& Trip::customerId() const noexcept { return customerId_; }
TripStatus Trip::status() const noexcept { std::lock_guard<std::mutex> lock(mutex_); return status_; }
double Trip::distanceKm() const noexcept { return distanceKm_; }
double Trip::quotedAmount() const noexcept { return quotedAmount_; }
const Location& Trip::pickup() const noexcept { return pickup_; }
const Location& Trip::destination() const noexcept { return destination_; }
std::vector<Driver*> Trip::notifiedDrivers() const { std::lock_guard<std::mutex> lock(mutex_); return notifiedDrivers_; }

void Trip::notifyDrivers(const std::vector<Driver*>& drivers) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (status_ != TripStatus::Requested) throw std::logic_error("Only requested trips can notify drivers");
    notifiedDrivers_.clear();
    for (Driver* driver : drivers) {
        if (driver && driver->status() == DriverStatus::Available) {
            notifiedDrivers_.push_back(driver);
            driver->receiveRideCall(id_);
        }
    }
}

Message Trip::acceptByDriver(Driver& driver) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (status_ != TripStatus::Requested) return failure("Trip is no longer available");
    if (driver.status() != DriverStatus::Available) return failure("Driver is not available");
    if (std::find(notifiedDrivers_.begin(), notifiedDrivers_.end(), &driver) == notifiedDrivers_.end()) {
        return failure("Driver was not notified for this trip");
    }
    assignedDriver_ = &driver;
    status_ = TripStatus::Accepted;
    driver.setStatus(DriverStatus::OnTrip);
    removePendingCallsLocked();
    return {true, "Trip accepted"};
}

Message Trip::start() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (status_ != TripStatus::Accepted) return failure("Only an accepted trip can start");
    status_ = TripStatus::InProgress;
    startTime_ = std::chrono::system_clock::now();
    return {true, "Trip started"};
}

Message Trip::complete() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (status_ != TripStatus::InProgress) return failure("Only an in-progress trip can complete");
    status_ = TripStatus::Completed;
    endTime_ = std::chrono::system_clock::now();
    if (assignedDriver_) assignedDriver_->setStatus(DriverStatus::Available);
    return {true, "Trip completed"};
}

Message Trip::cancel() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (status_ != TripStatus::Requested && status_ != TripStatus::Accepted) return failure("Trip cannot be cancelled now");
    status_ = TripStatus::Cancelled;
    if (assignedDriver_) assignedDriver_->setStatus(DriverStatus::Available);
    removePendingCallsLocked();
    return {true, "Trip cancelled"};
}

void Trip::removePendingCallsLocked() {
    for (Driver* driver : notifiedDrivers_) if (driver) driver->removeRideCall(id_);
}
