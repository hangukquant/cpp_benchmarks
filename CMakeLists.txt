cmake_minimum_required(VERSION 3.10)
project(binance_ws)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost REQUIRED COMPONENTS system thread)

add_executable(binance_ws src/main.cpp)

target_link_libraries(binance_ws PRIVATE Boost::system Boost::thread ssl crypto)
