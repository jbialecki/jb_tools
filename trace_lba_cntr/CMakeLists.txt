cmake_minimum_required (VERSION 2.8.11)

project (HELLO)

include_directories(../common)

add_executable (trace_lba_cntr 
		../common/lba_counter.cpp
		../common/log_convert.cpp
		main.cpp)
