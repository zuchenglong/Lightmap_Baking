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
	void InitRenderData(GLuint sharedVBO);
	void OnSceneRendering();
private:
	GLuint VAO, VBO;

	GLuint vertexShader;
	GLuint fragmentShader;

	GLuint shaderProgram;

	GLuint colorTexture;
	GLuint frameColorTexture;

	GLuint FBO;
private:
	void InitRenderBuffer();
	void InitRenderBuffer(GLuint sharedVBO);

	void InitShaderProgram();

	void InitFrameBuffer();

	void InitColorTexture();
};
