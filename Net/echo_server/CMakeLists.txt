set(CMAKE_CXX_FLAGS "-Wall -std=gnu++11 -g -O0 -pthread")

add_executable(
        echo_server
        echo_server.cpp
)

target_link_libraries(
		echo_server
)

