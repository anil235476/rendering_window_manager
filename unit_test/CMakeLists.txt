cmake_minimum_required(VERSION 3.7)
add_subdirectory(rendering_server_client)
add_subdirectory(signaller)

if(MSVC)
	#set_source_files_properties(${SOURCE_FILES}
	#	PROPERTIES COMPILE_FLAGS "/W3 /WX")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

endif()


add_executable( unit_test 
			main.cpp
			)

target_include_directories(unit_test PUBLIC 
	#$<BUILD_INTERFACE:${BOOST_LIB}>
	#$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/signaller/>
	#$<BUILD_INTERFACE:${CMAKE_HOME_DIRECTORY}/lib/signaller/>
	#$<BUILD_INTERFACE:${ABSL_PATH}>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/catch>
	)
	
target_link_directories( unit_test PUBLIC
"./rendering_server_client"
	$<BUILD_INTERFACE:${BOOST_LIB}/stage/lib>
	#$<BUILD_INTERFACE:${CMAKE_HOME_DIRECTORY}/webrtc_open_source/debug>
)



target_link_libraries( unit_test 
json_parser
rendering_server_client
signaller
func_thread_handler

)