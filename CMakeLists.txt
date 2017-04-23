cmake_minimum_required(VERSION 3.7)
project(malloc)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

set(SOURCE_FILES
        include/malloc.h
        sources/malloc.c
        sources/mem.c
        sources/realloc.c
        sources/show_alloc_mem.c)

add_executable(malloc ${SOURCE_FILES})