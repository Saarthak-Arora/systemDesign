#pragma once

#include <string>

class Vehicle {
public:
    Vehicle() = default;
    Vehicle(std::string registrationNumber, std::string model, std::string color);

    [[nodiscard]] const std::string& registrationNumber() const noexcept;
    [[nodiscard]] const std::string& model() const noexcept;
    [[nodiscard]] const std::string& color() const noexcept;
    [[nodiscard]] bool isRegistered() const noexcept;
    void update(std::string registrationNumber, std::string model, std::string color);
    void unregister() noexcept;

private:
    std::string registrationNumber_;
    std::string model_;
    std::string color_;
};
