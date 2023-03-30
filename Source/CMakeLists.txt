# CMakeList.txt : CMake project for Dynamic Lightmaps, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (${PROJECT_NAME} 
				${SOURCE_PATH}/main.cpp 
				${EXTERNAL_PATH}/glfw/deps/glad.c 
				${SOURCE_PATH}/Lightmap_Baking.cpp)

target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES})
