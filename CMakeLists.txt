# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

add_definitions(-DPROJECT_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

set(ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(SOURCE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Source)
set(EXTERNAL_PATH ${CMAKE_CURRENT_SOURCE_DIR}/External)
message("==============" ${SOURCE_PATH})

project ("Lightmap_Baking")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build the GLFW example programs")

include_directories(${PROJECT_SOURCE_DIR})

include_directories(${EXTERNAL_PATH}/stb)				# stb
include_directories(${EXTERNAL_PATH}/glm)				# glm
include_directories(${EXTERNAL_PATH}/glfw/deps)			# glad
include_directories(${EXTERNAL_PATH}/glfw/include)		# glfw
include_directories(${EXTERNAL_PATH}/assimp/include)	# assimp

add_subdirectory(Source)

add_subdirectory(${EXTERNAL_PATH}/glm)
add_subdirectory(${EXTERNAL_PATH}/glfw)
add_subdirectory(${EXTERNAL_PATH}/assimp)

add_definitions( "-D _CRT_SECURE_NO_WARNINGS -std=c99" )