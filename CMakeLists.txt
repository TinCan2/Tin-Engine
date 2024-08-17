cmake_minimum_required(VERSION 3.10)
project("Tin Engine" VERSION 1.0)

option(BUILD_SHARED_LIBS "Build the engine to be dynamically linked." OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES Source/Animation.cpp
			Source/GameManager.cpp
			Source/Rectangle.cpp
			Source/Camera.cpp
			Source/InputManager.cpp
			Source/Sprite.cpp
			Source/Circle.cpp
			Source/JointShape.cpp
			Source/Vector2D.cpp
			Source/CollisionInfo.cpp
			Source/Painter.cpp
			Source/Color.cpp
			Source/PhysicalObject.cpp)

add_library(tinEngine ${SOURCES})