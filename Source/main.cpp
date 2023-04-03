#include <thread>
#include <glad/glad.h>
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>

#include "Define.h"
#include "Light_Baking.h"
#include "Scene_Rendering.h"

using namespace std;

GLuint sharedVBO;

Scene_Rendering* sceneRendering = nullptr;
Light_Baking* lightBaking = nullptr;

void initVertexBuffers();
void bakeThread(GLFWwindow* bakeContext);

int main()
{
	cout << "Hello CMake." << endl;
	glfwInit();

	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//设置主版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//设置次版本号
	GLFWwindow* window = glfwCreateWindow(width, height, "LightmapBaking", NULL, NULL);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//使用核心模式

#if !DRAW_SCREEN_BAKETHREAD
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
#endif // DRAW_SCREEN_BAKETHREAD

	GLFWwindow* bakeContext = glfwCreateWindow(width, height, "RenderThread", nullptr, window);

	glfwMakeContextCurrent(window);

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1);

	sceneRendering = new Scene_Rendering(window);
#if MUTITHREAD_SHAREVBO
	initVertexBuffers();
	sceneRendering->InitRenderData(sharedVBO);
#else
	sceneRendering->InitRenderData();
#endif

#if ENABLE_BAKETHREAD
	std::thread bakeThread(bakeThread, bakeContext);
#endif // ENABLE_RENDERTHREAD

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	while (!glfwWindowShouldClose(window))	//主渲染线程
	{
		sceneRendering->OnSceneRendering();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

#if ENABLE_BAKETHREAD
	bakeThread.join();
#endif

	delete(sceneRendering);

	glfwMakeContextCurrent(NULL);
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

void initVertexBuffers()
{
	glGenBuffers(1, &sharedVBO);
	glBindBuffer(GL_ARRAY_BUFFER, sharedVBO);

	float vertices[] =
	{
		-0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.0f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.0f,  1.0f, 0.0f,

		-0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.0f,  1.0f, 1.0f
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void bakeThread(GLFWwindow* bakeContext)
{
	glfwMakeContextCurrent(bakeContext);

	lightBaking = new Light_Baking(bakeContext);

#if MUTITHREAD_SHAREVBO
	lightBaking->InitRenderData(sharedVBO);
#else
	lightBaking->InitRenderData();
#endif // MUTITHREAD_SHAREVBO

	while (!glfwWindowShouldClose(bakeContext))
	{
		lightBaking->OnBakeRendering();

		glfwSwapBuffers(bakeContext);
	}

	glfwMakeContextCurrent(NULL);
	glfwDestroyWindow(bakeContext);

	delete(lightBaking);
}