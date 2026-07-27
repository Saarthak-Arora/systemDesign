#pragma once

#include "Driver.hpp"

#include <vector>

[[nodiscard]] std::vector<Driver*> findNearestDrivers(const Location& customerLocation,
                                                       const std::vector<Driver*>& drivers,
                                                       double maxDistanceKm);
