// Lightmap_Baking.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// TODO: Reference additional headers your program requires here.

class Light_Baking
{
public:
	Light_Baking();
	Light_Baking(GLFWwindow* renderWindow);

	~Light_Baking();

	void InitRenderData();
	void OnBakeRendering();
private:
	GLuint vertexShader;
	GLuint fragmentShader;

	GLuint shaderProgram;

	GLuint VBO, VAO, EBO;

	GLuint ColorTexture;
	GLuint FrameColorTexture;

	GLuint FBO;
private:
	void InitRenderBuffer();

	void InitShaderProgram();

	void InitFrameBuffer();

	void InitColorTexture();
};
