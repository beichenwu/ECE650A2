cmake_minimum_required(VERSION 2.8.12.2)
project(a2-ece650)

set(CMAKE_CXX_STANDARD 98)

# create the main executable
add_executable(a2-ece650 a2-ece650.cpp)


# create the executable for tests
add_executable(tests test.cpp)
install(TARGETS a2-ece650 RUNTIME DESTINATION bin)