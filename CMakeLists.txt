cmake_minimum_required(VERSION 3.16)
project(unc_compatibility_runtime LANGUAGES CXX)

option(UNC_BUILD_TESTS "Build local unit tests" ON)

add_library(unc_modules
    functions/cache/Cache.cpp
    functions/console/Console.cpp
    functions/crypt/Crypt.cpp
    functions/drawing/Drawing.cpp
    functions/filesystem/filesystem.cpp
    functions/input/Input.cpp
    functions/misc/Misc.cpp
    functions/websocket/WebSocket.cpp
)
target_compile_features(unc_modules PUBLIC cxx_std_17)
target_include_directories(unc_modules PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/functions/cache
    ${CMAKE_CURRENT_SOURCE_DIR}/functions/console
    ${CMAKE_CURRENT_SOURCE_DIR}/functions/crypt
    ${CMAKE_CURRENT_SOURCE_DIR}/functions/drawing
    ${CMAKE_CURRENT_SOURCE_DIR}/functions/filesystem
    ${CMAKE_CURRENT_SOURCE_DIR}/functions/input
    ${CMAKE_CURRENT_SOURCE_DIR}/functions/misc
    ${CMAKE_CURRENT_SOURCE_DIR}/functions/websocket
)
if(MSVC)
    target_compile_options(unc_modules PRIVATE /W4 /permissive-)
else()
    target_compile_options(unc_modules PRIVATE -Wall -Wextra -Wpedantic)
endif()

if(UNC_BUILD_TESTS)
    enable_testing()
    add_executable(unc_tests tests/test_main.cpp)
    target_link_libraries(unc_tests PRIVATE unc_modules)
    add_test(NAME unc_tests COMMAND unc_tests)
endif()
