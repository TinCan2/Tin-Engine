#==Project Definitions==#
cmake_minimum_required(VERSION 3.10)
project("Tin Engine" VERSION 1.0.0 LANGUAGES CXX DESCRIPTION "A small modular game engine made using the SDL2 library")

#==C++ Standards==#
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#==Module Definitions==#
set(TIN_MODULES "CORE" "INPUT" "SHAPE" "SPRITE" "PAINTER" "PHYSICS" "ANIMATION" "VISUALS")

# User options for modules
set(TIN_MODULES_INCLUDE_CORE ON)
option(TIN_MODULES_INCLUDE_INPUT "Include the input module." ON)
option(TIN_MODULES_INCLUDE_SHAPE "Include the shape module." ON)
option(TIN_MODULES_INCLUDE_SPRITE "Include the sprite module." ON)
option(TIN_MODULES_INCLUDE_PAINTER "Include the painter module." ON)
option(TIN_MODULES_INCLUDE_PHYSICS "Include the physics module." ON)
option(TIN_MODULES_INCLUDE_ANIMATION "Include the animation module." ON)
option(TIN_MODULES_INCLUDE_VISUALS "Include the visuals module." ON)

# Define module dependencies
set(TIN_MODULES_DEPS_CORE)
set(TIN_MODULES_DEPS_INPUT CORE)
set(TIN_MODULES_DEPS_SHAPE CORE)
set(TIN_MODULES_DEPS_SPRITE CORE)
set(TIN_MODULES_DEPS_PAINTER SHAPE)
set(TIN_MODULES_DEPS_PHYSICS SHAPE)
set(TIN_MODULES_DEPS_ANIMATION SPRITE)
set(TIN_MODULES_DEPS_VISUALS ANIMATION)

# Define module files
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
            list(APPEND TIN_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/Source/${file}.cpp")
            list(APPEND TIN_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/Source/${file}.hpp")
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
option(TIN_BUILD_SHARED "Build the engine for dynamic linking." ON)
option(TIN_LINK_SDL_DYNAMIC "Link the SDL libraries dynamically to the engine." ON)

if(${TIN_BUILD_SHARED})
	set(TIN_BUILD_TYPE SHARED)
else()
	set(TIN_BUILD_TYPE STATIC)
endif()

add_library(tinEngine ${TIN_BUILD_TYPE} ${TIN_SOURCE})
target_include_directories(tinEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Source)

set_target_properties(tinEngine PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Tin Engine/lib")
set_target_properties(tinEngine PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Tin Engine/lib")


#==Dependency Management==#
include(FetchContent)
set(FETCHCONTENT_QUIET OFF)
FetchContent_Declare(SDL2 GIT_REPOSITORY https://github.com/libsdl-org/SDL.git GIT_TAG release-2.30.6 GIT_PROGRESS ON)
FetchContent_Declare(SDL2_image GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git GIT_TAG release-2.8.2 GIT_PROGRESS ON)

set(BUILD_SHARED_LIBS ${TIN_LINK_SDL_DYNAMIC})
FetchContent_MakeAvailable(SDL2 SDL2_image)

set(TIN_LINKED_LIBRARIES SDL2main SDL2_image)
if(${TIN_LINK_SDL_DYNAMIC})
	list(APPEND TIN_LINKED_LIBRARIES SDL2)
else()
	list(APPEND TIN_LINKED_LIBRARIES SDL2-static)
endif()

target_link_libraries(tinEngine ${TIN_LINKED_LIBRARIES})


#==Include&Deps Copying==#
set(TIN_INCLUDE_DIR "${CMAKE_BINARY_DIR}/Tin Engine/include")
file(MAKE_DIRECTORY ${TIN_INCLUDE_DIR})
add_custom_command(TARGET tinEngine POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${TIN_HEADER} ${TIN_INCLUDE_DIR})

if (${TIN_LINK_SDL_DYNAMIC})
	set(TIN_DEPS_DIR "${CMAKE_BINARY_DIR}/Tin Engine/deps")
	file(MAKE_DIRECTORY ${TIN_DEPS_DIR})
	add_custom_command(TARGET tinEngine POST_BUILD COMMAND
					   ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:SDL2> ${TIN_DEPS_DIR})
	add_custom_command(TARGET tinEngine POST_BUILD COMMAND
					   ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:SDL2_image> ${TIN_DEPS_DIR})
endif()


#==Exporting==#
#export(TARGETS tinEngine FILE tinEngineConfig.cmake)