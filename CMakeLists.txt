cmake_minimum_required(VERSION 3.5)

set(EXE_NAME rendering_window)
set(BOOST_LIB "D:/boost_1_69_0/boost_1_69_0")

ADD_DEFINITIONS(-D_UNICODE)
add_definitions(/ZI)

add_subdirectory(display_manager)
add_subdirectory(external_lib)
if(ENABLE_TEST)
set(SIGNALLER_LIB_PATH "D:/git_project/rendering_window_manager/unit_test")
set(JSON_INCLUDE "D:/git_project/rendering_window_manager/external_lib/json_parser/include")
set(JSON_LIB_PATH "D:/git_project/rendering_window_manager/external_lib")
	add_subdirectory(unit_test)
endif(ENABLE_TEST)
add_executable(${EXE_NAME} WIN32
main.cpp
button_handler.h
button_handler.cpp
)



# Add some compile flags to our source files.
if(MSVC)
	#set_source_files_properties(${SOURCE_FILES}
	#	PROPERTIES COMPILE_FLAGS "/W3 /WX")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
	
	target_compile_definitions(${EXE_NAME} PUBLIC
	NOMINMAX
)
else()
	set_source_files_properties(${SOURCE_FILES}
		PROPERTIES COMPILE_FLAGS -Wall -Wextra -Wpedantic)
endif()

target_include_directories(${EXE_NAME} PUBLIC
	"${PROJECT_SOURCE_DIR}/external_lib/json_parser/"
	"${PROJECT_SOURCE_DIR}/external_lib/websocket_server/"
	"${PROJECT_SOURCE_DIR}/external_lib/function_thread_handler/"
	"${PROJECT_SOURCE_DIR}/external_lib"
	"${LIBWEBRTC_INCLUDE_PATH}/third_party/abseil-cpp"
)


target_link_directories( ${EXE_NAME} PUBLIC
	$<BUILD_INTERFACE:${BOOST_LIB}/stage/lib>
)



# Public (interface) dependencies.
target_link_libraries(${EXE_NAME} PUBLIC
	display_manager
	websocket_server
	func_thread_handler
	json_parser
	
)




