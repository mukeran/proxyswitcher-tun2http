#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
BUILD_DIR="$ROOT_DIR/build/android"
ANDROID_NDK="${ANDROID_NDK:-${ANDROID_NDK_HOME:-/Users/bytedance/Library/Android/sdk/ndk/26.1.10909125}}"

if [ ! -d "$ANDROID_NDK" ]; then
  echo "NDK not found: $ANDROID_NDK"
  exit 1
fi

ABIS=(arm64-v8a armeabi-v7a x86_64)
for ABI in "${ABIS[@]}"; do
  OUT="$BUILD_DIR/$ABI"
  mkdir -p "$OUT"
  cmake -S "$ROOT_DIR" -B "$OUT" \
    -DANDROID=ON \
    -DCMAKE_SYSTEM_NAME=Android \
    -DANDROID_PLATFORM=android-24 \
    -DANDROID_ABI="$ABI" \
    -DCMAKE_ANDROID_NDK="$ANDROID_NDK" \
    -DCMAKE_TOOLCHAIN_FILE="$ANDROID_NDK/build/cmake/android.toolchain.cmake" \
    -DCMAKE_BUILD_TYPE=Release
  cmake --build "$OUT" --config Release -j
  echo "Built: $OUT/libproxyswitcher_tun2http.so"
done
