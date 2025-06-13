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

# Example using header-only cpp-httplib
add_executable(get_mids src/get_mids.cpp)
target_include_directories(get_mids PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
