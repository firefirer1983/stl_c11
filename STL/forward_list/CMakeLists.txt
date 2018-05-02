set(CMAKE_CXX_FLAGS "-Wall -std=gnu++11 -g -O0 -pthread")
set(googleTestDir ../../googletest)
include_directories(${googleTestDir}/googletest/include)

set(SOURCE
	forward_list.cpp
)

add_executable(forward_list
	${SOURCE}
)

target_link_libraries(
	forward_list
	gtest
)

