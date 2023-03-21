cmake_minimum_required(VERSION 3.20)

set(name xx2d_word_destroyer)
project(${name})

set(CMAKE_CXX_STANDARD 20)

include_directories(
	../xx2d/glad
	../xx2d/xxlib
	../xx2d/src
	../xx2d/headers
)

set(SRCS)
file(GLOB SRCS	#GLOB_RECURSE
	src/*.h
	src/*.hpp
	src/*.inc
	src/*.c
	src/*.cpp
)
source_group("" FILES ${SRCS})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SRCS})
add_executable(${name} ${SRCS})

add_subdirectory(../xx2d xx2d)
target_link_libraries(${name} xx2d glfw imgui pugixml libzstd_static)

if(MSVC)	# vs2022+

	set_source_files_properties(src/main.cpp PROPERTIES COMPILE_FLAGS "/Ycmain.h")
	target_compile_options(${name} PRIVATE $<$<PLATFORM_ID:Windows>:/Yumain.h>)

	add_compile_options($<$<PLATFORM_ID:Windows>:/MP${Biogears_BUILD_PARALLEL_LEVEL}>)	# other proj enable multi-processor compilation

	target_compile_options(${name}
		PRIVATE $<$<PLATFORM_ID:Windows>:/std:c17>
		PRIVATE $<$<PLATFORM_ID:Windows>:/bigobj>
		PRIVATE $<$<PLATFORM_ID:Windows>:/MP${Biogears_BUILD_PARALLEL_LEVEL}>	# this proj enable multi-processor compilation
	)

	set_target_properties(${name} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

endif()
