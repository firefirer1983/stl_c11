set(CMAKE_CXX_FLAGS "-Wall -std=gnu++11 -g -O0 -pthread")
set(googleTestDir ../../googletest)
include_directories(${googleTestDir}/googletest/include)

set(SOURCE
		 variadic_template.cpp
)

add_executable(variadic_template
	${SOURCE}
)

target_link_libraries(
		variadic_template
	gtest
)

