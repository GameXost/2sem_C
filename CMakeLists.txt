cmake_minimum_required(VERSION 3.30)
project(2sem C)

set(CMAKE_C_STANDARD 11)

add_library(2sem STATIC library.c
        laba3/stack.c
        laba3/stack.c
        laba4/oper.c)
