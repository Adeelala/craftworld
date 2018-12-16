# Tell CMake where to find Boost
set(BOOST_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../Libraries/boost")

# Find Boost
find_package(Boost REQUIRED COMPONENTS serialization)

# Set Boost linker flags
set(CMAKE_CXX_FLAGS "-pthread ${CMAKE_CXX_FLAGS}")

# Make common library headers available
include_directories(../Common/Source)
include_directories(${Boost_INCLUDE_DIRS})

# Add SAMOVAR target
file(GLOB_RECURSE SOURCES Source/*.cpp Source/*.hpp)
add_library(CraftWorld-SAMOVAR
	${SOURCES}
	)

# Link the common library and Boost
target_link_libraries(CraftWorld-SAMOVAR CraftWorld-Common)
target_link_libraries(CraftWorld-SAMOVAR ${Boost_LIBRARIES})
