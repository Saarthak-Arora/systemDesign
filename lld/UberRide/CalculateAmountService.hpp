#pragma once

enum class RideType { Standard, Premium, Pool };

[[nodiscard]] double calculateAmount(RideType rideType, double distanceKm);
