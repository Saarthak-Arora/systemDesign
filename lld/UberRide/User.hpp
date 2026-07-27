#pragma once

#include "Location.hpp"

#include <string>

class User {
public:
    User(std::string name, std::string email, std::string mobileNumber, Location location);
    virtual ~User() = default;

    [[nodiscard]] const std::string& id() const noexcept;
    [[nodiscard]] const std::string& name() const noexcept;
    [[nodiscard]] const std::string& email() const noexcept;
    [[nodiscard]] const std::string& mobileNumber() const noexcept;
    [[nodiscard]] const Location& currentLocation() const noexcept;
    void updateLocation(Location location);

private:
    std::string id_;
    std::string name_;
    std::string email_;
    std::string mobileNumber_;
    Location currentLocation_;
};
