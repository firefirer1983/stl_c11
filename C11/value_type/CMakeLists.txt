set(CMAKE_CXX_FLAGS "-Wall -std=gnu++11 -g -O0 -pthread")
set(googleTestDir ../../googletest)
include_directories(${googleTestDir}/googletest/include)

set(SOURCE
    value_type.cpp
)

add_executable(value_type
	${SOURCE}
)

target_link_libraries(
    value_type
	gtest
)

