cmake_minimum_required(VERSION 3.6)
project(malloc)

set(CMAKE_CXX_STANDARD 11)
include_directories(include)

set(SOURCE_FILES
        sources/malloc.c include/malloc.h sources/mem.c sources/show_alloc_mem.c)

add_executable(malloc ${SOURCE_FILES})