set(CMAKE_CXX_FLAGS "-Wall -std=gnu++11 -g -O0 -pthread")
set(googleTestDir ../../googletest)
include_directories(${googleTestDir}/googletest/include)

set(SOURCE
		inherit_construct_deconstruct.cpp
)

add_executable(inherit_construct_deconstruct
	${SOURCE}
)

target_link_libraries(
		inherit_construct_deconstruct
	gtest
)

