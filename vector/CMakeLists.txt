set(CMAKE_CXX_FLAGS "-Wall -std=c++11 -g -O0")

set(VECTOR
	vector.cpp
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

add_executable(vector-exe
	${VECTOR}
)

target_link_libraries(
	vector-exe
	${GTEST}
	${PTHREAD}
)

