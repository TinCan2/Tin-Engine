#==Project Definitions==#
cmake_minimum_required(VERSION 3.10)
project("Tin Engine" VERSION 1.0 LANGUAGES CXX)


#==C++ Standards==#
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)


#==Module Definitions==#
set(TIN_MODULES "CORE" "INPUT" "SHAPE" "SPRITE" "PAINTER" "PHYSICS" "ANIMATION" "VISUALS")

set(TIN_MODULES_INCLUDE_CORE ON)
option(TIN_MODULES_INCLUDE_INPUT "Include the input module." ON)
option(TIN_MODULES_INCLUDE_SHAPE "Include the shape module." ON)
option(TIN_MODULES_INCLUDE_SPRITE "Include the sprite module." ON)
option(TIN_MODULES_INCLUDE_PAINTER "Include the painter module." ON)
option(TIN_MODULES_INCLUDE_PHYSICS "Include the physics module." ON)
option(TIN_MODULES_INCLUDE_ANIMATION "Include the animation module." ON)
option(TIN_MODULES_INCLUDE_VISUALS "Include the visuals module." ON)

set(TIN_MODULES_DEPS_CORE)
set(TIN_MODULES_DEPS_INPUT CORE)
set(TIN_MODULES_DEPS_SHAPE CORE)
set(TIN_MODULES_DEPS_SPRITE CORE)
set(TIN_MODULES_DEPS_PAINTER SHAPE)
set(TIN_MODULES_DEPS_PHYSICS SHAPE)
set(TIN_MODULES_DEPS_ANIMATION SPRITE)
set(TIN_MODULES_DEPS_VISUALS ANIMATION)

set(TIN_MODULES_CORE_FILES "GameManager" "Vector2D" "Camera" "Color")
set(TIN_MODULES_INPUT_FILES "InputManager")
set(TIN_MODULES_SHAPE_FILES "Circle" "Rectangle" "JointShape")
set(TIN_MODULES_SPRITE_FILES "Sprite")
set(TIN_MODULES_PAINTER_FILES "Painter")
set(TIN_MODULES_PHYSICS_FILES "PhysicalObject" "CollisionInfo")
set(TIN_MODULES_ANIMATION_FILES "Animation")

#==Module Activation==#
set(TIN_SOURCE)
set(TIN_HEADER)

set(TIN_ACTIVATION_QUEUE)

foreach(module ${TIN_MODULES})
	if (${TIN_MODULES_INCLUDE_${module}})
		list(APPEND TIN_ACTIVATION_QUEUE ${module})
	endif()
endforeach()

while(NOT "${TIN_ACTIVATION_QUEUE}" STREQUAL "")
	foreach(module ${TIN_ACTIVATION_QUEUE})
		add_compile_definitions(TIN_MODULES_INCLUDE_${module})
		foreach(file ${TIN_MODULES_${module}_FILES})
			list(APPEND TIN_SOURCE "Source/${file}.cpp")
			list(APPEND TIN_HEADER "Source/${file}.hpp")
		endforeach()

		foreach(dep ${TIN_MODULES_DEPS_${module}})
			if (NOT ${TIN_MODULES_INCLUDE_${dep}})
				set(TIN_MODULES_INCLUDE_${dep} ON)
				list(APPEND TIN_ACTIVATION_QUEUE ${dep})
			endif()
		endforeach()

		list(REMOVE_ITEM TIN_ACTIVATION_QUEUE ${module})
	endforeach()
endwhile()

message(VERBOSE "Included modules with dependencies: ")
foreach(module ${TIN_MODULES})
	if (${TIN_MODULES_INCLUDE_${module}})
		message(VERBOSE ${module})
	endif()
endforeach()


#==Generation Process==#
option(BUILD_SHARED_LIBS "Build as a shared library." ON)
add_library(tinEngine ${TIN_SOURCE})

file(COPY ${TIN_HEADER} DESTINATION Include/)