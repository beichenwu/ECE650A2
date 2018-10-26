cmake_minimum_required(VERSION 2.8)
project(a2-ece650)

set (CMAKE_CXX_FLAGS "-std=c++98 -Wall ${CMAKE_CXX_FLAGS}")

# create the main executable
add_executable(a2-ece650 a2-ece650.cpp)


# create the executable for tests
add_executable(tests test.cpp)

