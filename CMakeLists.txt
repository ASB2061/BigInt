cmake_minimum_required(VERSION 3.1)
project(BigInt)

set(CMAKE_CXX_STANDARD 20)

add_executable(BigInt
		main.cpp
		SafeInt.cpp
		String.cpp
        BigInt.h DoubleInt.cpp DoubleInt.h BigInt.c big_int.h big_int.c)

include_directories(/home/courses/include ../HaverfordCS/include)
