#include "Customer.hpp"
#include "Driver.hpp"
#include "FindNearestDriver.hpp"
#include "Trip.hpp"

#include <iomanip>
#include <iostream>
#include <vector>

int main() {
    Customer customer{"Saarthak", "saarthak@example.com", "1234567890", {12.9716, 77.5946, "Bengaluru"}};
    Driver nearby{"Asha", "asha@example.com", "9876543210", "DL12345",
                  {"KA01AB1234", "Swift", "Red"}, {12.9900, 77.6000, "Bengaluru"}};
    Driver distant{"Ravi", "ravi@example.com", "9123456789", "DL67890",
                   {"KA02CD5678", "City", "Blue"}, {13.0827, 80.2707, "Chennai"}};

    Trip trip{customer, customer.currentLocation(), {12.9352, 77.6245, "Koramangala"}, RideType::Standard};
    std::vector<Driver*> drivers{&nearby, &distant};
    trip.notifyDrivers(findNearestDrivers(trip.pickup(), drivers, 10.0));

    std::cout << trip.id() << ": " << std::fixed << std::setprecision(2) << trip.distanceKm()
              << " km, quoted " << trip.quotedAmount() << '\n';
    if (const auto notified = trip.notifiedDrivers(); notified.empty()) {
        std::cout << "No drivers available nearby.\n";
        return 0;
    }
    const Message accepted = nearby.acceptRideCall(trip);
    std::cout << accepted.content << '\n';
    std::cout << trip.start().content << '\n';
    std::cout << trip.complete().content << '\n';
}
