cmake_minimum_required(VERSION 3.20)

project(TicketBooking VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_library(
TicketBooking SHARED
AmountDetail.cpp
BookShow.cpp
RoomShowSeatManager.cpp
serviceAvailable.cpp
User.cpp
)

target_include_directories(TicketBooking PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(TicketBookingApp main.cpp)
target_link_directories(TicketBookingApp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})