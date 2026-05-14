#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
BUILD_DIR="$ROOT_DIR/build/ios"
IOS_DEVICE_ARCHS="${IOS_DEVICE_ARCHS:-arm64;arm64e}"
IOS_SIM_ARCHS="${IOS_SIM_ARCHS:-arm64;x86_64}"

IOS_SDK="$(xcrun --sdk iphoneos --show-sdk-path)"
SIM_SDK="$(xcrun --sdk iphonesimulator --show-sdk-path)"

mkdir -p "$BUILD_DIR/device" "$BUILD_DIR/simulator"
rm -rf "$BUILD_DIR/device" "$BUILD_DIR/simulator"
mkdir -p "$BUILD_DIR/device" "$BUILD_DIR/simulator"

cmake -S "$ROOT_DIR" -B "$BUILD_DIR/device" \
  -DCMAKE_SYSTEM_NAME=iOS \
  -DCMAKE_OSX_ARCHITECTURES="$IOS_DEVICE_ARCHS" \
  -DCMAKE_OSX_SYSROOT="$IOS_SDK" \
  -DCMAKE_BUILD_TYPE=Release
cmake --build "$BUILD_DIR/device" --config Release -j

cmake -S "$ROOT_DIR" -B "$BUILD_DIR/simulator" \
  -DCMAKE_SYSTEM_NAME=iOS \
  -DCMAKE_OSX_ARCHITECTURES="$IOS_SIM_ARCHS" \
  -DCMAKE_OSX_SYSROOT="$SIM_SDK" \
  -DCMAKE_BUILD_TYPE=Release
cmake --build "$BUILD_DIR/simulator" --config Release -j

echo "Built iOS dylibs:"
echo "  $BUILD_DIR/device/libproxyswitcher_tun2http.dylib"
echo "  $BUILD_DIR/simulator/libproxyswitcher_tun2http.dylib"
