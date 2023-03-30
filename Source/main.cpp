#include <thread>
#include <mutex>
#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include "Lightmap_Baking.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <glm/glm.hpp>

// 主线程 画面是否上屏
#define DRAW_SCREEN_MAINLOOP
// 是否开启 渲染线程
#define ENABLE_RENDERTHREAD

using namespace std;

static std::string ProjectDir(PROJECT_DIR);

const unsigned int width = 800, height = 600;

GLuint vertexShader;
GLuint fragmentShader;

GLuint shaderProgram;

void initSceneProgram()
{
	const char* vertexShaderSource =
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	const char* fragmentShaderSource =
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
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

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

GLuint screenVertexShader;
GLuint screenFragmentShader;

GLuint screenShaderProgram;

void initScreenProgram()
{
	const char* vertexShaderSource =
		"#version 330 core\n"
		"layout (location = 0) in vec2 aPos;\n"
		"layout (location = 1) in vec2 aTexCoords;\n"

		"out vec2 TexCoords;\n"

		"void main()\n"
		"{\n"
		"   TexCoords = aTexCoords;\n"
		"   gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
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
		//"   FragColor = vec4(1.0, 1.0, 1.0, 1.0);\n"
		"}\n\0";

	screenVertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(screenVertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(screenVertexShader);

	screenFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(screenFragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(screenFragmentShader);

	screenShaderProgram = glCreateProgram();
	glAttachShader(screenShaderProgram, screenVertexShader);
	glAttachShader(screenShaderProgram, screenFragmentShader);
	glLinkProgram(screenShaderProgram);

	glUseProgram(screenShaderProgram);
	glUniform1i(glGetUniformLocation(screenShaderProgram, "screenTexture"), 0);

	glDeleteShader(screenVertexShader);
	glDeleteShader(screenFragmentShader);
}

GLuint VBO, VAO, EBO;

GLuint ColorTexture;
GLuint FrameColorTexture;

GLuint FBO;

void generateSceneBuffer()
{
	// 设置顶点数据
	float vertices[] = {
		 0.5f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};
	GLuint indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

GLuint screenVAO, screenVBO;

void generateScreenBuffer()
{
	float screenVertices[] =
	{
		// positions   // texCoords
		//-1.0f,  1.0f,  0.0f, 1.0f,
		//-1.0f, -1.0f,  0.0f, 0.0f,
		// 1.0f, -1.0f,  1.0f, 0.0f,

		//-1.0f,  1.0f,  0.0f, 1.0f,
		// 1.0f, -1.0f,  1.0f, 0.0f,
		// 1.0f,  1.0f,  1.0f, 1.0f

		-0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  1.0f, 0.0f,

		-0.5f,  0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  1.0f, 1.0f
	};

	glGenVertexArrays(1, &screenVAO);
	glGenBuffers(1, &screenVBO);

	glBindVertexArray(screenVAO);
	glBindBuffer(GL_ARRAY_BUFFER, screenVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(screenVertices), screenVertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void initScreen()
{
	initScreenProgram();
	generateScreenBuffer();
}

void initScene()
{
	initSceneProgram();
	generateSceneBuffer();
}

void initFramebuffer()
{
#if 1
	glGenTextures(1, &ColorTexture);
	glBindTexture(GL_TEXTURE_2D, ColorTexture);

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

#if 1
	glGenTextures(1, &FrameColorTexture);
	glBindTexture(GL_TEXTURE_2D, FrameColorTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, FrameColorTexture, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
#endif // 绑定Framebuffer
}

void destorySceneBuffer()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);
}

void destoryScreenBuffer()
{
	glDeleteVertexArrays(1, &screenVAO);
	glDeleteBuffers(1, &screenVBO);
	glDeleteProgram(screenShaderProgram);
}

void destoryBuffer()
{
	destorySceneBuffer();
	destoryScreenBuffer();
}

void mainLoop()
{
#ifndef DRAW_SCREEN_MAINLOOP
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
#endif // 

#if 1
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(screenShaderProgram);
	glUniform1i(glGetUniformLocation(screenShaderProgram, "screenTexture"), 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ColorTexture);

	glBindVertexArray(screenVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
#endif // 绘制 Texture

#ifndef DRAW_SCREEN_MAINLOOP
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
#endif

#ifndef DRAW_SCREEN_MAINLOOP
	glBindTexture(GL_TEXTURE_2D, FrameColorTexture);
	unsigned char* pixels = new unsigned char[width * height * 4];
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	stbi_write_png("output_Frame.png", width, height, 4, pixels, width * 4);
	delete[] pixels;
#endif // 写入 FrameTexture
}

void renderLoop()
{
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glViewport(0, 0, width, height);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

#if 1
	glBindTexture(GL_TEXTURE_2D, FrameColorTexture);
	unsigned char* pixels = new unsigned char[width * height * 4];
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	stbi_write_png("output_Frame_RenderLoop.png", width, height, 4, pixels, width * 4);
	delete[] pixels;
#endif // 写入 FrameTexture

#if 0
	glBindTexture(GL_TEXTURE_2D, ColorTexture);
	unsigned char* pixels = new unsigned char[512 * 512 * 3];
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
	stbi_write_png("output_Color.png", width, height, 3, pixels, width * 3);
	delete[] pixels;
#endif //写入 ColorTexture
}

void renderThread(GLFWwindow* renderWindow)
{
	//glfwMakeContextCurrent(renderWindow);

	while (!glfwWindowShouldClose(renderWindow))
	{
		renderLoop();
	}

	//glfwMakeContextCurrent(NULL);
	glfwDestroyWindow(renderWindow);
}

int main()
{
	cout << "Hello CMake." << endl;
	glfwInit();

	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//设置主版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//设置次版本号
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//使用核心模式
	GLFWwindow* window = glfwCreateWindow(width, height, "LightmapBaking", NULL, NULL);
	glfwMakeContextCurrent(window);

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1);

	initScene();
	initScreen();
	initFramebuffer();

	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
	GLFWwindow* renderWindow = glfwCreateWindow(width, height, "RenderThread", nullptr, window);

#ifdef ENABLE_RENDERTHREAD
	std::thread renderThread(renderThread, window);
#endif // ENABLE_RENDERTHREAD

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	while (!glfwWindowShouldClose(window))	//主渲染线程
	{
		mainLoop();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	renderThread.join();

	destoryBuffer();

	glfwMakeContextCurrent(NULL);
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}