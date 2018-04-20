set(CMAKE_CXX_FLAGS "-Wall -std=gnu++11 -g -O0 -pthread")
set(googleTestDir ../../googletest)
include_directories(${googleTestDir}/googletest/include)

set(SOURCE
		type_cast.cpp
)

add_executable(type_cast
	${SOURCE}
)

target_link_libraries(
		type_cast
	gtest
)

