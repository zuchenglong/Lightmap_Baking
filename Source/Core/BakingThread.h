// Lightmap_Baking.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// TODO: Reference additional headers your program requires here.

class BakingThread
{
public:
	BakingThread();
	BakingThread(GLFWwindow* renderWindow);

	~BakingThread();

	void Init();

	void Update();

	void InitRenderData();
	void InitRenderData(GLuint sharedVBO);
private:
	GLuint vertexShader;
	GLuint fragmentShader;

	GLuint shaderProgram;

	GLuint VBO, VAO;

	GLuint colorTexture;
	GLuint frameColorTexture;

	GLuint FBO;
private:
	void InitRenderBuffer();
	void InitRenderBuffer(GLuint sharedVBO);

	void InitShaderProgram();

	void InitFrameBuffer();

	void InitColorTexture();

	void OnBakeRendering();
};
