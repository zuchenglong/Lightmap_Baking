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
				
				${SOURCE_PATH}/Core/Input.cpp
				${SOURCE_PATH}/Core/Time.cpp

				${SOURCE_PATH}/Utils/TextureLoader.cpp
				${SOURCE_PATH}/Utils/ModelLoader.cpp

				${SOURCE_PATH}/Component/Mesh.cpp
				${SOURCE_PATH}/Component/Model.cpp
				${SOURCE_PATH}/Component/Camera.cpp 				
				${SOURCE_PATH}/Component/Shader.cpp
				${SOURCE_PATH}/Component/Material.cpp

				${SOURCE_PATH}/Application/Application.cpp
				${SOURCE_PATH}/Application/CameraController.cpp
				${SOURCE_PATH}/Application/Renderer/SceneBake.cpp
				${SOURCE_PATH}/Application/Renderer/SceneRenderer.cpp
)

include_directories(${SOURCE_PATH})
message(>>>>>>>>>>>>>>>>>>>> ${SOURCE_PATH})

target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES})
target_link_libraries(${PROJECT_NAME} assimp)