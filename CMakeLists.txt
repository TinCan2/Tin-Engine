#==Project Definitions==#
cmake_minimum_required(VERSION 3.11...3.30)
project("Tin Engine" VERSION 0.0.1 LANGUAGES CXX)


#==Module Definitions==#
set(TIN_MODULES CORE INPUT SHAPES SPRITE PAINTER PHYSICS ANIMATION FUNCTIONALS VISUALS TILES)

set(TIN_MODULES_INCLUDE_CORE ON)
option(TIN_MODULES_INCLUDE_INPUT "Include the input module." ON)
option(TIN_MODULES_INCLUDE_SHAPES "Include the shapes module." ON)
option(TIN_MODULES_INCLUDE_SPRITE "Include the sprite module." ON)
option(TIN_MODULES_INCLUDE_PAINTER "Include the painter module." ON)
option(TIN_MODULES_INCLUDE_PHYSICS "Include the physics module." ON)
option(TIN_MODULES_INCLUDE_ANIMATION "Include the animation module." ON)
option(TIN_MODULES_INCLUDE_FUNCTIONALS "Include the functionals module." ON)
option(TIN_MODULES_INCLUDE_VISUALS "Include the visuals module." ON)
option(TIN_MODULES_INCLUDE_TILES "Include the tiles module." ON)

set(TIN_MODULES_FILES_CORE GameManager Vector2D Camera Color)
set(TIN_MODULES_FILES_INPUT KeyboardManager MouseManager ControllerManager)
set(TIN_MODULES_FILES_SHAPES Circle Rectangle JointShape)
set(TIN_MODULES_FILES_SPRITE Sprite)
set(TIN_MODULES_FILES_PAINTER Painter)
set(TIN_MODULES_FILES_PHYSICS CollisionInfo PhysicalObject)
set(TIN_MODULES_FILES_ANIMATION Animation)
set(TIN_MODULES_FILES_FUNCTIONALS FunctionalObject)
set(TIN_MODULES_FILES_VISUALS VisualObject)
set(TIN_MODULES_FILES_TILES Tileset Tilemap)

set(TIN_MODULES_DEPS_CORE)
set(TIN_MODULES_DEPS_INPUT CORE)
set(TIN_MODULES_DEPS_SHAPES CORE)
set(TIN_MODULES_DEPS_SPRITE CORE)
set(TIN_MODULES_DEPS_PAINTER SHAPES)
set(TIN_MODULES_DEPS_PHYSICS SHAPES)
set(TIN_MODULES_DEPS_ANIMATION SPRITE)
set(TIN_MODULES_DEPS_FUNCTUIONALS CORE)
set(TIN_MODULES_DEPS_VISUALS ANIMATION)
set(TIN_MODULES_DEPS_TILES VISUALS)


#==Demo Definitions==#
option(TIN_BUILD_DEMOS "Build the demo executables for testing." OFF)
set(TIN_DEMOS CoreDemo GetKeyDemo InputDemo MouseDemo PhysicsDemo FunctionalsDemo AABBOptimizationDemo)
list(APPEND TIN_DEMOS ControllerDemo Sprite-AnimationDemo VisualsDemo FPVDemo TilesetDemo TilemapDemo)

set(TIN_DEMO_DEPS_CoreDemo CORE)
set(TIN_DEMO_DEPS_GetKeyDemo INPUT)
set(TIN_DEMO_DEPS_InputDemo INPUT)
set(TIN_DEMO_DEPS_MouseDemo INPUT)
set(TIN_DEMO_DEPS_PhysicsDemo PHYSICS)
set(TIN_DEMO_DEPS_FunctionalsDemo FUNCTIONALS)
set(TIN_DEMO_DEPS_AABBOptimizationDemo PHYSICS)
set(TIN_DEMO_DEPS_ControllerDemo INPUT)
set(TIN_DEMO_DEPS_VisualsDemo VISUALS INPUT)
set(TIN_DEMO_DEPS_FPVDemo FUNCTIONALS PHYSICS VISUALS INPUT)
set(TIN_DEMO_DEPS_TilesetDemo TILES)

if(${TIN_BUILD_DEMOS})
	foreach(demo ${demos})
		foreach (dep ${TIN_DEMO_DEPS_${demo}})
			set(TIN_MODULES_INCLUDE_${dep} ON)
		endforeach()
	endforeach()
endif()


#==Module Activation==#
set(TIN_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Source)

set(TIN_SOURCE)
set(TIN_HEADER ${TIN_SOURCE_DIR}/DllMacro.hpp ${TIN_SOURCE_DIR}/TinEngine.hpp ${TIN_SOURCE_DIR}/ModuleDefinitions.hpp)

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

configure_file(${TIN_SOURCE_DIR}/ModuleDefinitions.hpp.in ${TIN_SOURCE_DIR}/ModuleDefinitions.hpp)


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
FetchContent_Declare(SDL2_image GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git GIT_TAG release-2.8.2 GIT_PROGRESS ON)

set(SDL_SHARED ${TIN_LINK_SDL_DYNAMIC})
if (${TIN_LINK_SDL_DYNAMIC})
	set(SDL_STATIC OFF)
else()
	set(SDL_STATIC ON)
endif()

set(BUILD_SHARED_LIBS ${TIN_LINK_SDL_DYNAMIC})
FetchContent_MakeAvailable(SDL2 SDL2_image)

set(TIN_LINK_LIST "SDL2_image")
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

set_target_properties(SDL2_image PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${TIN_OUTPUT_DIR}/deps")
set_target_properties(SDL2_image PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${TIN_OUTPUT_DIR}/deps")
set_target_properties(SDL2_image PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${TIN_OUTPUT_DIR}/deps")

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

if (WIN32 AND TIN_BUILD_DEMOS)
	if (TIN_BUILD_SHARED)
		add_custom_command(TARGET tinEngine POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
							$<TARGET_FILE:tinEngine> ${TIN_OUTPUT_DIR}/demos/$<CONFIG>)
	endif()
	if (TIN_LINK_SDL_DYNAMIC)
		add_custom_command(TARGET tinEngine POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
								$<TARGET_FILE:SDL2> ${TIN_OUTPUT_DIR}/demos/$<CONFIG>)
		add_custom_command(TARGET tinEngine POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
								$<TARGET_FILE:SDL2_image> ${TIN_OUTPUT_DIR}/demos/$<CONFIG>)
	endif()
endif()


#==Demo Generation==#
if (${TIN_BUILD_DEMOS})
	add_custom_command(TARGET tinEngine PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
						"${CMAKE_CURRENT_SOURCE_DIR}/Demos/Sprites" ${TIN_OUTPUT_DIR}/demos/Sprites)

	foreach(demo ${TIN_DEMOS})
		add_executable(${demo} "${CMAKE_CURRENT_SOURCE_DIR}/Demos/${demo}.cpp")

		target_link_libraries(${demo} PRIVATE tinEngine)
		target_include_directories(${demo} PRIVATE "${TIN_OUTPUT_DIR}/include")
		target_compile_definitions(${demo} PUBLIC TIN_DEMO_LOCATION=\"${TIN_OUTPUT_DIR}/demos/\")
		set_target_properties(${demo} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${TIN_OUTPUT_DIR}/demos")
		set_target_properties(${demo} PROPERTIES FOLDER "Demos")
	endforeach()
endif()