# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

add_definitions(-DPROJECT_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
add_definitions(-DPROJECT_ASSETS_DIR="${CMAKE_CURRENT_SOURCE_DIR}/Assets")

set(ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(SOURCE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Source)
set(EXTERNAL_PATH ${CMAKE_CURRENT_SOURCE_DIR}/External)
set(Assets_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Assets)

project ("Lightmap_Baking")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build the GLFW example programs")

include_directories(${EXTERNAL_PATH}/stb)				# stb
include_directories(${EXTERNAL_PATH}/glm)				# glm

add_subdirectory(${EXTERNAL_PATH}/glfw)
include_directories(${EXTERNAL_PATH}/glfw/deps)			# glad
include_directories(${EXTERNAL_PATH}/glfw/include)		# glfw

add_subdirectory(${EXTERNAL_PATH}/assimp)
include_directories(${EXTERNAL_PATH}/assimp/include)	# assimp

add_library(xatlas ${EXTERNAL_PATH}/xatlas/xatlas.cpp)	# xatlas
target_include_directories(xatlas INTERFACE ${EXTERNAL_PATH}/xatlas)

add_subdirectory(Source)
include_directories(${PROJECT_SOURCE_DIR}/Source)				# src

add_definitions( "-D _CRT_SECURE_NO_WARNINGS -std=c99" )
