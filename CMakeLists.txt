cmake_minimum_required(VERSION 3.24)
project(TripCostCalculator)

set(CMAKE_CXX_STANDARD 23)

add_executable(TripCostCalculator main.cpp Menu.cpp Menu.h User.cpp User.h Trip.cpp Trip.h Cost.cpp Cost.h)