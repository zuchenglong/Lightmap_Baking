#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Component/Model.h"
#include "Component/Shader.h"

class SceneRenderer
{
public:
	SceneRenderer();
	SceneRenderer(GLFWwindow*);
	virtual ~SceneRenderer();

	void Init();

	void Tick();

	void InitRenderData();
	void InitRenderData(GLuint sharedVBO);
private:
	GLuint VAO, VBO;

	GLuint vertexShader;
	GLuint fragmentShader;

	GLuint shaderProgram;

	GLuint colorTexture;
	GLuint frameColorTexture;

	GLuint FBO;

	Model* m_Model;
	Shader* m_Shader;
private:
	void InitRenderBuffer();
	void InitRenderBuffer(GLuint sharedVBO);

	void InitShaderProgram();

	void InitFrameBuffer();

	void InitColorTexture();

	void OnSceneRendering();
};
