cmake_minimum_required(VERSION 3.10)
project(proxyswitcher_tun2http C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(T2H_SOURCES
    src/ios_shim/stub.c
)

if(ANDROID)
    set(T2H_SOURCES
        src/dhcp.c
        src/dns.c
        src/icmp.c
        src/ip.c
        src/http.c
        src/tun2http.c
        src/session.c
        src/tcp.c
        src/tls.c
        src/udp.c
        src/util.c
    )
endif()

if(ANDROID)
    add_library(proxyswitcher_tun2http SHARED ${T2H_SOURCES})
else()
    add_library(proxyswitcher_tun2http STATIC ${T2H_SOURCES})
endif()

if(ANDROID)
    find_library(LOG_LIB log)
    target_link_libraries(proxyswitcher_tun2http ${LOG_LIB})
endif()

set_target_properties(proxyswitcher_tun2http PROPERTIES
    OUTPUT_NAME "proxyswitcher_tun2http"
)

option(BUILD_TESTING "Build tests" ON)
if(BUILD_TESTING)
    enable_testing()

    add_executable(tun2http_tests
        tests/test_main.c
        tests/test_common.h
        tests/test_util.c
        tests/test_dns.c
        tests/test_http.c
        tests/test_stubs.c
        src/dns.c
        src/http.c
    )
    target_include_directories(tun2http_tests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/tests
    )
    target_compile_definitions(tun2http_tests PRIVATE UNIT_TEST=1)
    target_compile_options(tun2http_tests PRIVATE -Wall -Wextra)

    add_test(NAME tun2http_tests COMMAND tun2http_tests)
endif()
