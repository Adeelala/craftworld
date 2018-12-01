# Make common library headers available
include_directories(../Common/Source)

file(GLOB_RECURSE SOURCES Source/*.cpp)

#set(BOOST_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../Libraries/boost_1_68_0")
#set(BOOST_LIBRARYDIR "${CMAKE_CURRENT_SOURCE_DIR}/../../Libraries/boost_1_68_0")
#set(BOOST_NO_SYSTEM_PATHS ON)
#set(Boost_USE_STATIC_LIBS ON)
#set(Boost_USE_MULTITHREADED ON)
#set(Boost_DEBUG 1)
#find_package(Boost 1.68.0 REQUIRED COMPONENTS asio)
#
#if(Boost_FOUND)
#	include_directories(${Boost_INCLUDE_DIRS})
#	# Add server target
	add_executable(Craftworld-Server
			${SOURCES}
			)

	# Link the common library and boost
	target_link_libraries(Craftworld-Server Craftworld-Common)
#endif()