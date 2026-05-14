#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
BUILD_DIR="$ROOT_DIR/build/ios"

IOS_SDK="$(xcrun --sdk iphoneos --show-sdk-path)"
SIM_SDK="$(xcrun --sdk iphonesimulator --show-sdk-path)"

mkdir -p "$BUILD_DIR/device" "$BUILD_DIR/simulator"

cmake -S "$ROOT_DIR" -B "$BUILD_DIR/device" \
  -DCMAKE_SYSTEM_NAME=iOS \
  -DCMAKE_OSX_ARCHITECTURES=arm64 \
  -DCMAKE_OSX_SYSROOT="$IOS_SDK" \
  -DCMAKE_BUILD_TYPE=Release
cmake --build "$BUILD_DIR/device" --config Release -j

cmake -S "$ROOT_DIR" -B "$BUILD_DIR/simulator" \
  -DCMAKE_SYSTEM_NAME=iOS \
  -DCMAKE_OSX_ARCHITECTURES="arm64;x86_64" \
  -DCMAKE_OSX_SYSROOT="$SIM_SDK" \
  -DCMAKE_BUILD_TYPE=Release
cmake --build "$BUILD_DIR/simulator" --config Release -j

echo "Built iOS dylibs:"
echo "  $BUILD_DIR/device/libproxyswitcher_tun2http.dylib"
echo "  $BUILD_DIR/simulator/libproxyswitcher_tun2http.dylib"
