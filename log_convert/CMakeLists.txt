cmake_minimum_required (VERSION 2.8.11)

project (HELLO)

include_directories(../common)

add_executable (log_convert 
		main.cpp
		../common/log_convert.cpp)
