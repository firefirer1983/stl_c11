set(CMAKE_CXX_FLAGS "-Wall -std=c++11 -g -O0 -pthread")
set(googleTestDir ../googletest)
include_directories(${googleTestDir}/googletest/include)

set(SOURCE
	array.cpp
)

add_executable(array
	${SOURCE}
)

target_link_libraries(
	array
	gtest
)

