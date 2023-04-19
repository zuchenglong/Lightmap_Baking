#include <thread>
#include <glad/glad.h>
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>

#include "Define.h"
#include "Core/Time.h"
#include "Core/Input.h"
#include "Core/BakingThread.h"
#include "Core/RenderingThread.h"

#include "Application/Application.h"

using namespace std;

GLuint m_SharedVBO;

Application* m_Appliation = nullptr;

RenderingThread* m_RenderingThread = nullptr;
BakingThread* m_BakingThread = nullptr;

void InitSharingVertexBuffers();
void InitBakeThread(GLFWwindow* bakeContext);

int main()
{
	cout << "Hello CMake." << endl;
	glfwInit();

	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//设置主版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//设置次版本号
	GLFWwindow* window = glfwCreateWindow(width, height, "LightmapBaking", NULL, NULL);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//使用核心模式

#pragma region Input Callback
	glfwSetKeyCallback(window, KeyEventCallback);
	glfwSetMouseButtonCallback(window, MouseButtonEventCallback);
	glfwSetScrollCallback(window, MouseScrollCallback);
	glfwSetCursorPosCallback(window, MousePositionCallback);
#pragma endregion

#if !DRAW_SCREEN_BAKETHREAD
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
#endif // DRAW_SCREEN_BAKETHREAD

	GLFWwindow* bakeContext = glfwCreateWindow(width, height, "BakeThread", nullptr, window);

	glfwMakeContextCurrent(window);

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1);

	Input::Init();
	Time::Init();

	m_RenderingThread = new RenderingThread(window);
	m_RenderingThread->Init();

	m_Appliation = new Application();
	m_Appliation->Init();

#if MUTITHREAD_SHAREVBO
	InitSharingVertexBuffers();
	m_RenderingThread->InitRenderData(m_SharedVBO);
#else
	m_RenderingThread->InitRenderData();
#endif

#if ENABLE_BAKETHREAD
	std::thread BakingThread(InitBakeThread, bakeContext);
#endif // ENABLE_RENDERTHREAD

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	while (!glfwWindowShouldClose(window))	//主渲染线程
	{
		m_RenderingThread->Tick();
		m_Appliation->Tick();
		Input::Tick();
		Time::Tick();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

#if ENABLE_BAKETHREAD
	BakingThread.join();
#endif

	delete(m_RenderingThread);

	glfwMakeContextCurrent(NULL);
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

void InitSharingVertexBuffers()
{
	glGenBuffers(1, &m_SharedVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_SharedVBO);

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

void InitBakeThread(GLFWwindow* bakeContext)
{
	glfwMakeContextCurrent(bakeContext);

	m_BakingThread = new BakingThread(bakeContext);
	m_BakingThread->Init();

#if MUTITHREAD_SHAREVBO
	m_BakingThread->InitRenderData(m_SharedVBO);
#else
	m_BakingThread->InitRenderData();
#endif // MUTITHREAD_SHAREVBO

	while (!glfwWindowShouldClose(bakeContext))
	{
		m_BakingThread->Tick();

		glfwSwapBuffers(bakeContext);
	}

	glfwMakeContextCurrent(NULL);
	glfwDestroyWindow(bakeContext);

	delete(m_BakingThread);
}

