#pragma once
#include "SceneRenderer.h"

#include "Define.h"
#include "Component/Camera.h"
#include "Utils/ModelLoader.h"

#include "stb_image.h"
#include "stb_image_write.h"

using namespace std;

SceneRenderer::SceneRenderer()
{

}

SceneRenderer::SceneRenderer(GLFWwindow* window)
{
	glfwMakeContextCurrent(window);
}

void SceneRenderer::Init()
{
	m_Model = new Model();
	ModelLoader::Get()->LoadModel(ProjectAssetsDir + "/Models/Scene.obj", m_Model);
	m_Model->Init();
}

void SceneRenderer::Tick()
{
	m_Model->Render();
	OnSceneRendering();
}

void SceneRenderer::InitRenderData()
{
	InitRenderBuffer();
	InitShaderProgram();

	InitFrameBuffer();
	InitColorTexture();
}

void SceneRenderer::InitRenderData(GLuint sharedVBO)
{
	InitRenderBuffer(sharedVBO);
	InitShaderProgram();

	InitFrameBuffer();
	InitColorTexture();
}

void SceneRenderer::InitRenderBuffer()
{
	float screenVertices[] =
	{
		// positions		// texCoords
		-0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.0f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.0f,  1.0f, 0.0f,

		-0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.0f,  1.0f, 1.0f
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(screenVertices), screenVertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void SceneRenderer::InitRenderBuffer(GLuint sharedVBO)
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, sharedVBO);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void SceneRenderer::InitShaderProgram()
{
	const char* vertexShaderSource =
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec2 aTexCoords;\n"

		"out vec2 TexCoords;\n"

		"void main()\n"
		"{\n"
		"   TexCoords = aTexCoords;\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	const char* fragmentShaderSource =
		"#version 330 core\n"
		"out vec4 FragColor;\n"

		"in vec2 TexCoords;\n"
		"uniform sampler2D screenTexture;\n"

		"void main()\n"
		"{\n"
		"   vec3 col = texture(screenTexture, TexCoords).rgb;\n"
		"   FragColor = vec4(col, 1.0);\n"
		"}\n\0";

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glUseProgram(shaderProgram);
	glUniform1i(glGetUniformLocation(shaderProgram, "screenTexture"), 0);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void SceneRenderer::InitFrameBuffer()
{
#if 1
	glGenTextures(1, &frameColorTexture);
	glBindTexture(GL_TEXTURE_2D, frameColorTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, frameColorTexture, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
#endif // ∞Û∂®Framebuffer
}

void SceneRenderer::InitColorTexture()
{
#if 1
	glGenTextures(1, &colorTexture);
	glBindTexture(GL_TEXTURE_2D, colorTexture);

	string tex_path = ProjectDir + "/Assets/Texture/container.jpg";
	int nwidth, nheight, nrComponents;
	unsigned char* data = stbi_load(tex_path.c_str(), &nwidth, &nheight, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
		{
			format = GL_RED;
		}
		else if (nrComponents == 3)
		{
			format = GL_RGB;
		}
		else if (nrComponents == 4)
		{
			format = GL_RGBA;
		}
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, format, nwidth, nheight, 0, format, GL_UNSIGNED_BYTE, data);
		size_t length = strlen(reinterpret_cast<const char*>(data));
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_CLAMP_TO_EDGE);
		unsigned char color[] = { 255,0,255,255 };
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, color);

		stbi_image_free(data);
	}
#endif // F
}

void SceneRenderer::OnSceneRendering()
{
	Camera::GetMainCamera()->UpdateCameraTransform();

#if !DRAW_SCREEN_MAINTHREAD
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
#endif // 

	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(shaderProgram);
	glUniform1i(glGetUniformLocation(shaderProgram, "screenTexture"), 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, colorTexture);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);

#if !DRAW_SCREEN_MAINTHREAD
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
#endif

#if !DRAW_SCREEN_MAINTHREAD
	glBindTexture(GL_TEXTURE_2D, FrameColorTexture);
	unsigned char* pixels = new unsigned char[width * height * 4];
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	stbi_write_png("output_Frame_MainThread.png", width, height, 4, pixels, width * 4);
	delete[] pixels;
#endif // –¥»Î FrameTexture
}

SceneRenderer::~SceneRenderer()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
}