# proxyswitcher-tun2http

Extracted standalone project for ProxySwitcher tun2http native implementation.

## Layout

- `src/`: core C implementation (migrated from proxyswitcher-android)
- `include/`: public headers
- `scripts/build-android.sh`: build Android shared libs (`.so`)
- `scripts/build-ios.sh`: build iOS shared libs (`.dylib`)

## Build Android

Requirements:

- Android NDK (default path used: `/Users/bytedance/Library/Android/sdk/ndk/26.1.10909125`)

Run:

```bash
./scripts/build-android.sh
```

Output:

- `build/android/<abi>/libproxyswitcher_tun2http.so`

## Build iOS

Run:

```bash
./scripts/build-ios.sh
```

Output:

- `build/ios/device/libproxyswitcher_tun2http.dylib`
- `build/ios/simulator/libproxyswitcher_tun2http.dylib`

## Notes

- Current source is Android JNI-oriented C implementation migrated as-is.
- For production iOS integration, JNI-dependent parts should be replaced with platform-neutral callback interfaces.
