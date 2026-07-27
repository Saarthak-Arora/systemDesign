#include "CalculateAmountService.hpp"

#include <stdexcept>

double calculateAmount(RideType rideType, double distanceKm) {
    if (distanceKm < 0.0) throw std::invalid_argument("Distance cannot be negative");
    switch (rideType) {
        case RideType::Standard: return 40.0 + 12.0 * distanceKm;
        case RideType::Premium: return 80.0 + 20.0 * distanceKm;
        case RideType::Pool: return 25.0 + 8.0 * distanceKm;
    }
    throw std::invalid_argument("Unsupported ride type");
}
