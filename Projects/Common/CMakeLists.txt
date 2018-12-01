# Make Boost library headers available
include_directories(${Boost_INCLUDE_DIRS})

# Add common library target
file(GLOB_RECURSE SOURCES Source/*.cpp)
add_library(Craftworld-Common
	${SOURCES}
	)

# Link Boost
target_link_libraries(Craftworld-Common ${Boost_LIBRARIES})
