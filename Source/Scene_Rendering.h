#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Scene_Rendering
{
public:
	Scene_Rendering();
	Scene_Rendering(GLFWwindow*);
	~Scene_Rendering();

	void InitRenderData();
	void OnSceneRendering();
private:
	GLuint screenVAO, screenVBO;

	GLuint screenVertexShader;
	GLuint screenFragmentShader;

	GLuint screenShaderProgram;

	GLuint ColorTexture;
	GLuint FrameColorTexture;

	GLuint FBO;
private:
	void InitRenderBuffer();

	void InitShaderProgram();

	void InitFrameBuffer();

	void InitColorTexture();
};
