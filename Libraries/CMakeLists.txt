set(BOOST_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/boost")

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost COMPONENTS asio mpi serialization)

if(Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
endif()

#set(BOOST_LIBRARYDIR "${CMAKE_CURRENT_SOURCE_DIR}/../../Libraries/boost_1_68_0")
#set(BOOST_NO_SYSTEM_PATHS ON)
#set(Boost_USE_STATIC_LIBS ON)
#set(Boost_USE_MULTITHREADED ON)
#set(Boost_DEBUG 1)
#find_package(Boost 1.68.0 REQUIRED COMPONENTS asio)
#
#if(Boost_FOUND)
#	include_directories(${Boost_INCLUDE_DIRS})
