#==Project Definitions==#
cmake_minimum_required(VERSION 3.11...3.30)
project("Tin Engine" VERSION 1.0.0 LANGUAGES CXX)


#==Module Definitions==#
set(TIN_MODULES "CORE" "INPUT" "SHAPES" "SPRITE" "PAINTER" "PHYSICS" "ANIMATION")

set(TIN_MODULES_INCLUDE_CORE ON)
option(TIN_MODULES_INCLUDE_INPUT "Include the input module." ON)
option(TIN_MODULES_INCLUDE_SHAPES "Include the shapes module." ON)
option(TIN_MODULES_INCLUDE_SPRITE "Include the sprite module." ON)
option(TIN_MODULES_INCLUDE_PAINTER "Include the painter module." ON)
option(TIN_MODULES_INCLUDE_PHYSICS "Include the physics module." ON)
option(TIN_MODULES_INCLUDE_ANIMATION "Include the animation module." ON)

set(TIN_MODULES_FILES_CORE "GameManager" "Vector2D" "Camera" "Color")
set(TIN_MODULES_FILES_INPUT "InputManager")
set(TIN_MODULES_FILES_SHAPES "Circle" "Rectangle" "JointShape")
set(TIN_MODULES_FILES_SPRITE "Sprite")
set(TIN_MODULES_FILES_PAINTER "Painter")
set(TIN_MODULES_FILES_PHYSICS "CollisionInfo" "PhysicalObject")
set(TIN_MODULES_FILES_ANIMATION "Animation")

set(TIN_MODULES_DEPS_CORE)
set(TIN_MODULES_DEPS_INPUT "CORE")
set(TIN_MODULES_DEPS_SHAPES "CORE")
set(TIN_MODULES_DEPS_SPRITE "CORE")
set(TIN_MODULES_DEPS_PAINTER "SHAPES")
set(TIN_MODULES_DEPS_PHYSICS "CollisionInfo" "PhysicalObject")
set(TIN_MODULES_DEPS_ANIMATION "Sprite")