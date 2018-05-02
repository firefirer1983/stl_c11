set(CMAKE_CXX_FLAGS "-Wall -std=gnu++11 -g -O0 -pthread")
set(googleTestDir ../../googletest)
include_directories(${googleTestDir}/googletest/include)

set(SOURCE
		smart_pointer.cpp
)

add_executable(smart_pointer
	${SOURCE}
)

target_link_libraries(
		smart_pointer
	gtest
)

