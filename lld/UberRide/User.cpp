#include "User.hpp"

#include <atomic>
#include <stdexcept>
#include <utility>

namespace {
std::atomic<unsigned long long> nextUserId{1};
}

User::User(std::string name, std::string email, std::string mobileNumber, Location location)
    : id_("user-" + std::to_string(nextUserId.fetch_add(1))), name_(std::move(name)), email_(std::move(email)),
      mobileNumber_(std::move(mobileNumber)), currentLocation_(std::move(location)) {
    if (name_.empty() || email_.empty() || mobileNumber_.empty()) {
        throw std::invalid_argument("User name, email, and mobile number are required");
    }
}

const std::string& User::id() const noexcept { return id_; }
const std::string& User::name() const noexcept { return name_; }
const std::string& User::email() const noexcept { return email_; }
const std::string& User::mobileNumber() const noexcept { return mobileNumber_; }
const Location& User::currentLocation() const noexcept { return currentLocation_; }
void User::updateLocation(Location location) { currentLocation_ = std::move(location); }
