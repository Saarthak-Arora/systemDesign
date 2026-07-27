#include "Customer.hpp"
#include "Driver.hpp"
#include "FindNearestDriver.hpp"
#include "Trip.hpp"

#include <cassert>
#include <cmath>

int main() {
    Customer customer{"Customer", "customer@example.com", "1111111111", {12.9716, 77.5946}};
    Driver driver{"Driver", "driver@example.com", "2222222222", "DL1", {"KA01", "Sedan", "Black"},
                  {12.9800, 77.5946}};
    Driver farDriver{"Far", "far@example.com", "3333333333", "DL2", {"KA02", "SUV", "White"},
                     {28.7041, 77.1025}};
    assert(customer.currentLocation().distanceToKm(customer.currentLocation()) < 0.001);
    assert(findNearestDrivers(customer.currentLocation(), {&driver, &farDriver}, 5.0).size() == 1);

    Trip trip{customer, customer.currentLocation(), {12.9816, 77.5946}, RideType::Standard};
    assert(trip.quotedAmount() > 40.0);
    trip.notifyDrivers({&driver});
    assert(driver.acceptRideCall(trip).success);
    assert(!farDriver.acceptRideCall(trip).success);
    assert(trip.start().success);
    assert(trip.complete().success);
    assert(trip.status() == TripStatus::Completed);
    assert(driver.status() == DriverStatus::Available);
}
