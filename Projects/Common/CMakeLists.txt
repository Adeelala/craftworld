# Tell CMake where to find Boost
set(BOOST_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../Libraries/boost")

# Find Boost
find_package(Boost REQUIRED COMPONENTS serialization)

# Make Boost library headers available
set(Boost_INCLUDE_DIRS "../../Libraries/boost/include")
include_directories(${Boost_INCLUDE_DIRS})

# Add common library target
file(GLOB_RECURSE SOURCES Source/*.cpp)
add_library(Craftworld-Common
	${SOURCES}
	)

# Link Boost
target_link_libraries(Craftworld-Common ${Boost_LIBRARIES})
