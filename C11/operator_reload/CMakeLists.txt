set(CMAKE_CXX_FLAGS "-Wall -std=gnu++11 -g -O0 -pthread")
set(googleTestDir ../../googletest)
include_directories(${googleTestDir}/googletest/include)

set(SOURCE
		operator_reload.cpp
)

add_executable(operator_reload
	${SOURCE}
)

target_link_libraries(
		operator_reload
	gtest
)

