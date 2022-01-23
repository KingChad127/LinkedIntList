cmake_minimum_required(VERSION 3.21)
project(LinkedIntList C)

set(CMAKE_C_STANDARD 99)

add_executable(LinkedList linked_int_list.c node.h node.c linked_int_list.h)
