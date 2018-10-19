cmake_minimum_required(VERSION 2.8.12.2)
project(ece650a2)

set(CMAKE_CXX_STANDARD 98)

# create the main executable
add_executable(ece650a2 a2ece650.cpp)


# create the executable for tests
add_executable(tests test.cpp)