set(CMAKE_CXX_FLAGS "-Wall -std=gnu++11 -g -O0 -pthread")
set(googleTestDir ../../googletest)
include_directories(${googleTestDir}/googletest/include)


add_executable(vector
	vector.cpp
)
add_executable(vector2
		vector2.cpp
		)
target_link_libraries(
	vector
	gtest
)
target_link_libraries(
		vector2
		gtest
)

