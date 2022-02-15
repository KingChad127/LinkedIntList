cmake_minimum_required(VERSION 3.10)
project(LinkedIntList C)

set(CMAKE_C_STANDARD 11)

add_executable(LinkedList linked_int_list.c node.h node.c linked_int_list.h)
