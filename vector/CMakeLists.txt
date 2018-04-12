set(CMAKE_CXX_FLAGS "-Wall -std=c++11 -g -O0 -pthread")
set(googleTestDir ../googletest)
include_directories(${googleTestDir}/googletest/include)

set(SOURCE
	vector.cpp
)

add_executable(vector
	${SOURCE}
)

target_link_libraries(
	vector
	gtest
)

