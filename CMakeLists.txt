# Minimum required CMake version
cmake_minimum_required(VERSION 3.10)

# Project name
project(oscilloscope)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Specify the directories for your source and header files
include_directories(lib)
include_directories(include)
file(GLOB SOURCES "src/*.cpp")

# Find the required packages
find_package(raylib REQUIRED)
# Create the executable
add_executable(oscilloscope ${SOURCES})

# Link libraries
target_link_libraries(oscilloscope raylib)
