set(CMAKE_CXX_FLAGS "-Wall -std=gnu++11 -g -O0 -pthread")
set(googleTestDir ../../googletest)
include_directories(${googleTestDir}/googletest/include)

set(SOURCE
    rvalue.cpp
)

add_executable(rvalue
	${SOURCE}
)

target_link_libraries(
    rvalue
	gtest
)

