# Tell CMake where to find Boost
set(BOOST_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../Libraries/boost")

# Find Boost
find_package(Boost REQUIRED COMPONENTS serialization)

# Set Boost linker flags
set(CMAKE_CXX_FLAGS "-pthread ${CMAKE_CXX_FLAGS}")

# Make common and Boost library headers available
include_directories(../Common/Source)
include_directories(${Boost_INCLUDE_DIRS})

# Add client target
file(GLOB_RECURSE SOURCES Source/*.cpp Source/*.hpp)
add_executable(CraftWorld-Client
	${SOURCES}
	)

# Link the common library and Boost
target_link_libraries(CraftWorld-Client CraftWorld-Common ${Boost_LIBRARIES})
