# Make common library headers available
include_directories(../Common/Source)

# Add server target
file(GLOB_RECURSE SOURCES Source/*.cpp)
add_executable(Craftworld-Server
	${SOURCES}
	)

# Link the common library
target_link_libraries(Craftworld-Server Craftworld-Common)
