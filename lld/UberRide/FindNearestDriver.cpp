#include "FindNearestDriver.hpp"

#include <algorithm>
#include <stdexcept>

std::vector<Driver*> findNearestDrivers(const Location& customerLocation, const std::vector<Driver*>& drivers,
                                        double maxDistanceKm) {
    if (maxDistanceKm < 0.0) throw std::invalid_argument("Search radius cannot be negative");
    std::vector<Driver*> matches;
    for (Driver* driver : drivers) {
        if (driver != nullptr && driver->status() == DriverStatus::Available &&
            customerLocation.distanceToKm(driver->currentLocation()) <= maxDistanceKm) matches.push_back(driver);
    }
    std::sort(matches.begin(), matches.end(), [&customerLocation](const Driver* left, const Driver* right) {
        return customerLocation.distanceToKm(left->currentLocation()) < customerLocation.distanceToKm(right->currentLocation());
    });
    return matches;
}
