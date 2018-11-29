# Configure CMake
cmake_minimum_required(VERSION 3.12.3)

# Set up project
project(craftworld CXX)
set(CMAKE_CXX_STANDARD 17)

# Add external libraries
add_subdirectory(Libraries)

# Add projects
add_subdirectory(Projects)
