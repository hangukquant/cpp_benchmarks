# cpp_benchmarks

This sample project requires several libraries, namely `fmt`, `Boost.Beast`, `Boost.Asio`, and OpenSSL. These can be installed easily through [vcpkg](https://github.com/microsoft/vcpkg).

## Installing dependencies with vcpkg

```bash
# clone vcpkg if you do not already have it
git clone https://github.com/microsoft/vcpkg.git
./vcpkg/bootstrap-vcpkg.sh

# install required packages (example for 64-bit Linux)
./vcpkg/vcpkg install fmt boost-beast boost-asio openssl:x64-linux
```

When configuring CMake, use the `vcpkg.cmake` toolchain file:

```bash
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build
```

## Running the executable

After building, run the produced binary from the build directory:

```bash
./build/main
```

The program connects to Binance's WebSocket trade stream and prints messages.

## Header-only example

The `get_mids` target demonstrates using the header-only [cpp-httplib](https://github.com/yhirose/cpp-httplib)
library. It performs a simple HTTP GET request to Binance's `midPrice` endpoint.
Build and run it from the build directory:

```bash
./build/get_mids
```
