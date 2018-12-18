# Tell CMake where to find Boost and MPI
set(BOOST_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../Libraries/boost")
set(ENV{LD_LIBRARY_PATH} /usr/local/lib)

# Find Boost and MPI
find_package(Boost REQUIRED COMPONENTS serialization mpi)
find_package(MPI REQUIRED)

# Set Boost linker flags
set(CMAKE_CXX_FLAGS "-pthread ${CMAKE_CXX_FLAGS}")

# Make common, Boost and MPI library headers available
include_directories(/usr/local/include)
include_directories(../Common/Source)
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${MPI_INCLUDE_PATH})

# Add server target
file(GLOB_RECURSE SOURCES Source/*.cpp Source/*.hpp)
add_executable(CraftWorld-Server
	${SOURCES}
	)

# Link the common and Boost libraries
target_link_libraries(CraftWorld-Server CraftWorld-Common ${MPI_LIBRARIES} ${Boost_LIBRARIES})

if(MPI_COMPILE_FLAGS)
	set_target_properties(CraftWorld-Server PROPERTIES
		COMPILE_FLAGS "${MPI_COMPILE_FLAGS}")
endif()

if(MPI_LINK_FLAGS)
	set_target_properties(CraftWorld-Server PROPERTIES
		LINK_FLAGS "${MPI_LINK_FLAGS}")
endif()

message(${MPI_CXX_COMPILER})