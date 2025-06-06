cmake_minimum_required(VERSION 3.10)
project(main)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(fmt CONFIG REQUIRED)
find_package(Boost REQUIRED COMPONENTS beast asio)
find_package(OpenSSL REQUIRED)

add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE
    fmt::fmt
    Boost::beast
    Boost::asio
    OpenSSL::SSL
    OpenSSL::Crypto
)