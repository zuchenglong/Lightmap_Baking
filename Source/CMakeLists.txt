# CMakeList.txt : CMake project for Dynamic Lightmaps, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (
				${PROJECT_NAME} 
				${EXTERNAL_PATH}/glfw/deps/glad.c 

				${SOURCE_PATH}/main.cpp 
				${SOURCE_PATH}/Define.cpp 				
				${SOURCE_PATH}/Light_Baking.cpp
				${SOURCE_PATH}/Scene_Rendering.cpp
				)

target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES})
