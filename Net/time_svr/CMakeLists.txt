set(CMAKE_CXX_FLAGS "-Wall -std=gnu++11 -g -O0 -pthread")
set(googleTestDir ../../googletest)
include_directories(${googleTestDir}/googletest/include)

set(SOURCE
        time_svr.cpp
)

add_executable(time_svr
	${SOURCE}
)

target_link_libraries(
		time_svr
	gtest
)

