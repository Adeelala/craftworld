# Make common library headers available
include_directories(../Common/Source)

# Add SAMOVAR target
file(GLOB_RECURSE SOURCES Source/*.cpp Source/*.hpp)
add_executable(CraftWorld-SAMOVAR
	${SOURCES}
	)

# Link the common library and Boost
target_link_libraries(CraftWorld-SAMOVAR CraftWorld-Common)
