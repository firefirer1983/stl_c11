set(CMAKE_CXX_FLAGS "-Wall -std=c++11 -g -O0 -pthread")
set(googleTestDir ../googletest)
include_directories(${googleTestDir}/googletest/include)

set(SOURCE
	unordered_set.cpp
)

add_executable(unordered_set
	${SOURCE}
)

target_link_libraries(
	unordered_set
	gtest
)

