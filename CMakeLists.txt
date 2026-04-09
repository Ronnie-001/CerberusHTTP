# Name of project and CMake version
cmake_minimum_required(VERSION 3.23)
project(multithreaded-http-server)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# TODO: Set the libraries for the project (parser, response, router, etc.)



# TODO: Link the executable with the libraries
add_executable(Server)

target_sources(Server
    PRIVATE
        src/server/server.cpp
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS src/include
        FILES src/include/server.h
)
