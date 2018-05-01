set(CMAKE_CXX_FLAGS "-Wall -std=gnu++11 -g -O0 -pthread")

add_executable(
		echo_client
		echo_client.cpp
)

target_link_libraries(
		echo_client
)

