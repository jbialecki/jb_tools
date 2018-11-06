cmake_minimum_required (VERSION 2.8.11)

project (HELLO)

include_directories(../common)

add_executable (cmd_2_csv
		main.cpp
		../common/txt_utils.cpp
		../common/param_convert.cpp
		../common/log_convert.cpp)
