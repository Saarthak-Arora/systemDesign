#include "elevatorManager.hpp"

#include <chrono>
#include <memory>
#include <thread>

int main() {
    ElevatorManager manager{2};
    manager.submitRequest(std::make_shared<Request>(1, 0, 6));
    manager.submitRequest(std::make_shared<Request>(2, 3, 8));
    manager.submitRequest(std::make_shared<Request>(3, 2, 0));
    std::this_thread::sleep_for(std::chrono::seconds(2));
}
