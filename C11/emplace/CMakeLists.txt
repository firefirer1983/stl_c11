set(CMAKE_CXX_FLAGS "-Wall -std=gnu++11 -g -O0 -pthread")
set(googleTestDir ../../googletest)
include_directories(${googleTestDir}/googletest/include)

set(SOURCE
    emplace.cpp
)

add_executable(emplace
	${SOURCE}
)

target_link_libraries(
    emplace
	gtest
)

