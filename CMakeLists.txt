# Name of project and CMake version.
cmake_minimum_required(VERSION 3.23)
project(cerberus)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories("${CMAKE_SOURCE_DIR}/include")

# Enable compile commands to work with clangd LSP.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include the subdirectories.
add_subdirectory(src/server)
add_subdirectory(src/parser)
add_subdirectory(src/thread_pool)
add_subdirectory(src/router)
add_subdirectory(src/utility)
add_subdirectory(src/response)
add_subdirectory(src/tests)

# Include GTest as a dependency.
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG 063de7e9578f82b369302001269680b4b1553359
)
FetchContent_MakeAvailable(googletest)


add_executable(Server main.cpp)

target_link_libraries(Server 
    PRIVATE cerberus_server 
            cerberus_parser
            cerberus_thread_pool
            cerberus_router
            cerberus_utility
            cerberus_response
            cerberus_tests
)
