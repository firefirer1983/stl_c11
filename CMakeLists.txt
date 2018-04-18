cmake_minimum_required(VERSION 3.1)

project(str_c11)


add_subdirectory(googletest)

add_subdirectory(BASIC/inherit_construct_deconstruct)
add_subdirectory(BASIC/variadic_macro)

add_subdirectory(STL/array)
add_subdirectory(STL/bitset)
add_subdirectory(STL/deque)
add_subdirectory(STL/forward_list)
add_subdirectory(STL/list)
add_subdirectory(STL/map)
add_subdirectory(STL/queue)
add_subdirectory(STL/set)
add_subdirectory(STL/stack)
add_subdirectory(STL/unordered_map)
add_subdirectory(STL/unordered_set)
add_subdirectory(STL/vector)

add_subdirectory(C11/rvalue)
add_subdirectory(C11/emplace)
add_subdirectory(C11/value_type)
add_subdirectory(C11/smart_pointer)
add_subdirectory(C11/operator_reload)
add_subdirectory(C11/variadic_template)
add_subdirectory(C11/bind)


add_subdirectory(CONCURRENCY/test_and_set)


