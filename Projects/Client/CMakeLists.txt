# Make common library headers available
include_directories(../Common/Source)

# Add client target
file(GLOB_RECURSE SOURCES Source/*.cpp)
add_executable(Craftworld-Client
	${SOURCES}
	)

# Link the common library
target_link_libraries(Craftworld-Client Craftworld-Common)