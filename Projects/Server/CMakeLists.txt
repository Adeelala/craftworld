# Make common and Boost library headers available
include_directories(../Common/Source)
include_directories(${Boost_INCLUDE_DIRS})

# Add server target
file(GLOB_RECURSE SOURCES Source/*.cpp)
add_executable(Craftworld-Server
	${SOURCES}
	)

# Link the common library and Boost
target_link_libraries(Craftworld-Server Craftworld-Common)
target_link_libraries(Craftworld-Server ${Boost_LIBRARIES})
