set(CMAKE_CXX_FLAGS "-Wall -std=gnu++11 -g -O0 -pthread")

add_executable(
		echo_client
		echo_client.cpp
)

add_executable(
		echo_server
		echo_server.cpp
)

