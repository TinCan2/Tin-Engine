#==Project Definitions==#
cmake_minimum_required(VERSION 3.11...3.30)
project("Tin Engine" VERSION 0.0.1 LANGUAGES CXX)


#==Module Definitions==#
set(TIN_MODULES CORE)

set(TIN_MODULES_INCLUDE_CORE ON)

set(TIN_MODULES_FILES_CORE GameManager Vector2D Camera Color)

set(TIN_MODULES_DEPS_CORE)


#==Demo Definitions==#
set(TIN_DEMOS CoreDemo)

option(TIN_DEMO_BUILD_CoreDemo "Build the Core Demo." OFF)

set(TIN_DEMO_DEPS_CoreDemo CORE)

foreach(demo ${TIN_DEMOS})
	if (${TIN_DEMO_BUILD_${demo}})
		foreach (dep ${TIN_DEMO_DEPS_${demo}})
			set(TIN_MODULES_INCLUDE_${dep} ON)
		endforeach()
	endif()
endforeach()


#==Module Activation==#
set(TIN_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Source)

set(TIN_SOURCE)
set(TIN_HEADER)

set(TIN_ACTIVATION_QUEUE)
foreach(module ${TIN_MODULES})
	if (${TIN_MODULES_INCLUDE_${module}})
		list(APPEND TIN_ACTIVATION_QUEUE ${module})
	endif()
endforeach()

while(TIN_ACTIVATION_QUEUE)
	list(GET TIN_ACTIVATION_QUEUE 0 module)

	foreach(file ${TIN_MODULES_FILES_${module}})
		list(APPEND TIN_SOURCE "${TIN_SOURCE_DIR}/${file}.cpp")
		list(APPEND TIN_HEADER "${TIN_SOURCE_DIR}/${file}.hpp")
	endforeach()

	foreach(dep ${TIN_MODULES_DEPS_${module}})
		if (NOT ${TIN_MODULES_INCLUDE_${dep}})
			list(APPEND TIN_ACTIVATION_QUEUE ${dep})
			set(TIN_MODULES_INCLUDE_${dep} ON)
		endif()
	endforeach()

	list(REMOVE_ITEM TIN_ACTIVATION_QUEUE ${module})
endwhile()


#==Library Generation==#
option(TIN_BUILD_SHARED "Build the engine to be linked dynamically." ON)
option(TIN_LINK_SDL_DYNAMIC "Link the SDL libraries dynamically to the engine." ON)

set(BUILD_SHARED_LIBS ${TIN_BUILD_SHARED})
add_library(tinEngine ${TIN_SOURCE} ${TIN_HEADER})

target_compile_features(tinEngine PUBLIC cxx_std_20)
if (WIN32)
	target_compile_definitions(tinEngine PUBLIC TIN_EXPORTS)
endif()


#==Dependency Management==#
include(FetchContent)
set(FETCHCONTENT_QUIET OFF)
FetchContent_Declare(SDL2 GIT_REPOSITORY https://github.com/libsdl-org/SDL.git GIT_TAG release-2.30.6 GIT_PROGRESS ON)

set(SDL_SHARED ${TIN_LINK_SDL_DYNAMIC})
if (${TIN_LINK_SDL_DYNAMIC})
	set(SDL_STATIC OFF)
else()
	set(SDL_STATIC ON)
endif()

set(BUILD_SHARED_LIBS ${TIN_LINK_SDL_DYNAMIC})
FetchContent_MakeAvailable(SDL2)

set(TIN_LINK_LIST)
if (${TIN_LINK_SDL_DYNAMIC})
	list(APPEND TIN_LINK_LIST SDL2)
else()
	list(APPEND TIN_LINK_LIST SDL2-static)
endif()

target_link_libraries(tinEngine PRIVATE ${TIN_LINK_LIST})


#==Library Output Config==#
set(TIN_OUTPUT_DIR "${CMAKE_BINARY_DIR}/Tin-Engine Build")

set_target_properties(tinEngine PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${TIN_OUTPUT_DIR}/engine")
set_target_properties(tinEngine PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${TIN_OUTPUT_DIR}/engine")
set_target_properties(tinEngine PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${TIN_OUTPUT_DIR}/engine")

if (${TIN_LINK_SDL_DYNAMIC})
	set_target_properties(SDL2 PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${TIN_OUTPUT_DIR}/deps")
	set_target_properties(SDL2 PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${TIN_OUTPUT_DIR}/deps")
	set_target_properties(SDL2 PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${TIN_OUTPUT_DIR}/deps")
else()
	set_target_properties(SDL2-static PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${TIN_OUTPUT_DIR}/deps")
	set_target_properties(SDL2-static PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${TIN_OUTPUT_DIR}/deps")
	set_target_properties(SDL2-static PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${TIN_OUTPUT_DIR}/deps")
endif()

file(MAKE_DIRECTORY "${TIN_OUTPUT_DIR}/include")
add_custom_command(TARGET tinEngine PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${TIN_HEADER} ${TIN_OUTPUT_DIR}/include)


#==Demo Generation==#
foreach(demo ${TIN_DEMOS})
	if (${TIN_DEMO_BUILD_${demo}})
		add_executable(${demo} "${CMAKE_CURRENT_SOURCE_DIR}/Demos/${demo}.cpp")

		target_link_libraries(${demo} PRIVATE tinEngine)
		target_include_directories(${demo} PRIVATE "${TIN_OUTPUT_DIR}/include")
		target_compile_definitions(${demo} PUBLIC TIN_DEMO_LOCATION=\"${TIN_OUTPUT_DIR}/demos/\")
		set_target_properties(${demo} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${TIN_OUTPUT_DIR}/demos")
		set_target_properties(${demo} PROPERTIES FOLDER "Demos")
	endif()
endforeach()