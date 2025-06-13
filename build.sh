# Detect architecture
ARCH=$(uname -m)
OS=$(uname)

if [[ "$OS" == "Darwin" ]]; then
    if [[ "$ARCH" == "arm64" ]]; then
        TRIPLET="arm64-osx"
    else
        TRIPLET="x64-osx"
    fi
elif [[ "$OS" == "Linux" ]]; then
    if [[ "$ARCH" == "x86_64" ]]; then
        TRIPLET="x64-linux"
    else
        TRIPLET="arm64-linux"
    fi
else
    echo "Unsupported OS/arch"
    exit 1
fi

cmake -S . -B build \
  -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake \
  -DVCPKG_TARGET_TRIPLET=$TRIPLET

cmake --build build