cmake_minimum_required(VERSION 3.7)

add_definitions(/ZI)

if(MSVC)
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
	
endif()

add_library(utility
	executor/executor.h
	executor/executor.cpp
	function_duration_observer.h
	function_duration_observer.cpp
	stlab/task.hpp
	stlab/concurrency/config.hpp
	)

target_include_directories(utility PUBLIC 
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	)
