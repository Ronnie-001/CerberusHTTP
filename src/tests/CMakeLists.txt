cmake_minimum_required(VERSION 3.23)

# Create the object files for linking.
add_library(cerberus_tests
    STATIC server_test.cpp
)

target_include_directories(cerberus_tests
    PUBLIC "${PROJECT_SOURCE_DIR}/include"
    # Include GTest and GMock
    PUBLIC "${PROJECT_SOURCE_DIR}/build/_deps/googletest-src/googletest/include"
    PUBLIC "${PROJECT_SOURCE_DIR}/build/_deps/googletest-src/googlemock/include"
)
