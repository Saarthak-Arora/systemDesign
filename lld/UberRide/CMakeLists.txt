cmake_minimum_required(VERSION 3.20)
project(UberRide VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(uberride
    CalculateAmountService.cpp
    Driver.cpp
    FindNearestDriver.cpp
    Location.cpp
    Trip.cpp
    User.cpp
    Vehicle.cpp
)
target_include_directories(uberride PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options(uberride PRIVATE -Wall -Wextra -Wpedantic -Werror)

add_executable(uberride_demo main.cpp)
target_link_libraries(uberride_demo PRIVATE uberride)

include(CTest)
if(BUILD_TESTING)
    add_executable(uberride_tests tests.cpp)
    target_link_libraries(uberride_tests PRIVATE uberride)
    add_test(NAME uberride_tests COMMAND uberride_tests)
endif()
