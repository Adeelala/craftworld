# Tell CMake where to find Boost
set(BOOST_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/boost")

# Find Boost
find_package(Boost REQUIRED COMPONENTS serialization)
