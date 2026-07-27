#include "Location.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace {
constexpr double kEarthRadiusKm = 6371.0;
constexpr double kPi = 3.14159265358979323846;
constexpr double toRadians(double degrees) noexcept { return degrees * kPi / 180.0; }
}

Location::Location(double latitude, double longitude, std::string address)
    : latitude_(latitude), longitude_(longitude), address_(std::move(address)) {
    if (latitude < -90.0 || latitude > 90.0 || longitude < -180.0 || longitude > 180.0) {
        throw std::invalid_argument("Location coordinates are outside valid ranges");
    }
}

double Location::latitude() const noexcept { return latitude_; }
double Location::longitude() const noexcept { return longitude_; }
const std::string& Location::address() const noexcept { return address_; }

double Location::distanceToKm(const Location& other) const noexcept {
    const double deltaLatitude = toRadians(other.latitude_ - latitude_);
    const double deltaLongitude = toRadians(other.longitude_ - longitude_);
    const double latitude1 = toRadians(latitude_);
    const double latitude2 = toRadians(other.latitude_);
    const double a = std::sin(deltaLatitude / 2.0) * std::sin(deltaLatitude / 2.0) +
                     std::cos(latitude1) * std::cos(latitude2) *
                         std::sin(deltaLongitude / 2.0) * std::sin(deltaLongitude / 2.0);
    return kEarthRadiusKm * 2.0 * std::atan2(std::sqrt(a), std::sqrt(1.0 - std::min(1.0, a)));
}
