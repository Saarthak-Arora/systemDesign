#pragma once

#include <string>

class Location {
public:
    Location() = default;
    Location(double latitude, double longitude, std::string address = {});

    [[nodiscard]] double latitude() const noexcept;
    [[nodiscard]] double longitude() const noexcept;
    [[nodiscard]] const std::string& address() const noexcept;
    [[nodiscard]] double distanceToKm(const Location& other) const noexcept;

private:
    double latitude_{0.0};
    double longitude_{0.0};
    std::string address_;
};
