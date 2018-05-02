set(CMAKE_CXX_FLAGS "-Wall -std=gnu++11 -g -O0 -pthread")
set(googleTestDir ../../googletest)
include_directories(${googleTestDir}/googletest/include)

set(SOURCE
	array.cpp
        ../../Net/echo_client/uni.h ../../Net/echo_client/rwops.h)

add_executable(array
	${SOURCE}
)

target_link_libraries(
	array
	gtest
)

