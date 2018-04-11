set(CMAKE_CXX_FLAGS "-Wall -std=c++11 -g -O0")

set(FORWARD_LIST
	forward_list.cpp
)

include_directories("${PROJECT_SOURCE_DIR}/../googletest/googletest/include")

find_library(GTEST
	NAMES "gtest"
	PATHS ${PROJECT_SOURCE_DIR}/../googletest/build/googlemock/gtest/
	NO_DEFAULT_PATH
)

find_library(PTHREAD
	NAMES "pthread"
	PATHS /usr/lib/x86_64-linux-gnu/
	NO_DEFAULT_PATH)

add_executable(forward_list-exe
	${FORWARD_LIST}
)

target_link_libraries(
	forward_list-exe
	${GTEST}
	${PTHREAD}
)

