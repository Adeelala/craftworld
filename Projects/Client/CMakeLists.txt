# Make common and Boost library headers available
set(Boost_INCLUDE_DIRS "../../Libraries/boost/include")
include_directories(../Common/Source)
include_directories(${Boost_INCLUDE_DIRS})

# Add client target
file(GLOB_RECURSE SOURCES Source/*.cpp)
add_executable(Craftworld-Client
	${SOURCES}
	)

# Link the common library and Boost
target_link_libraries(Craftworld-Client Craftworld-Common)
target_link_libraries(Craftworld-Client ${Boost_LIBRARIES})
