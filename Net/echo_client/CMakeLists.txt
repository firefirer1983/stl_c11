set(CMAKE_CXX_FLAGS "-Wall -std=gnu++11 -g -O0 -pthread")

add_executable(
		client_select
		client_select.cpp
		rwops.cpp
)

add_executable(
		server_select
		server_select.cpp
		rwops.cpp
)

add_executable(
		echo_client
		echo_client.cpp
		rwops.cpp
)
add_executable(
		echo_server
		echo_server.cpp
		rwops.cpp
		signalproc.cpp
)

