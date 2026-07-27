#include "Vehicle.hpp"

#include <stdexcept>
#include <utility>

Vehicle::Vehicle(std::string registrationNumber, std::string model, std::string color) {
    update(std::move(registrationNumber), std::move(model), std::move(color));
}

const std::string& Vehicle::registrationNumber() const noexcept { return registrationNumber_; }
const std::string& Vehicle::model() const noexcept { return model_; }
const std::string& Vehicle::color() const noexcept { return color_; }
bool Vehicle::isRegistered() const noexcept { return !registrationNumber_.empty(); }

void Vehicle::update(std::string registrationNumber, std::string model, std::string color) {
    if (registrationNumber.empty() || model.empty()) {
        throw std::invalid_argument("Vehicle registration number and model are required");
    }
    registrationNumber_ = std::move(registrationNumber);
    model_ = std::move(model);
    color_ = std::move(color);
}

void Vehicle::unregister() noexcept { registrationNumber_.clear(); model_.clear(); color_.clear(); }
