set(CMAKE_CXX_FLAGS "-Wall -std=gnu++11 -g -O0 -pthread")
set(googleTestDir ../../googletest)
include_directories(${googleTestDir}/googletest/include)

set(SOURCE
		variadic_macro.cpp
)

add_executable(variadic_macro
	${SOURCE}
)

target_link_libraries(
		variadic_macro
	gtest
)

