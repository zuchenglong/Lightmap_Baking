#include <functional>
#include "Application.h"


Application::Application()
{
}

void Application::Init(GLFWwindow* window)
{
	CameraController::Get()->Init();

	m_SceneRenderer = new SceneRenderer(window);
	m_SceneRenderer->Init();

#if MUTITHREAD_SHAREVBO
	InitSharingVertexBuffers();
	m_SceneRenderer->InitRenderData(m_SharedVBO);
#else
	m_SceneRenderer->InitRenderData();
#endif

	GLFWwindow* bakeContext = glfwCreateWindow(width, height, "BakeThread", nullptr, window);
#if ENABLE_BAKETHREAD
	m_BakeThread = thread(&Application::InitBakeThread,this,bakeContext);
#endif // ENABLE_RENDERTHREAD
}

void Application::Tick()
{
	CameraController::Get()->Tick();
	m_SceneRenderer->Tick();
}

void Application::InitSharingVertexBuffers()
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

void Application::InitBakeThread(GLFWwindow* bakeContext)
{
	glfwMakeContextCurrent(bakeContext);

	m_SceneBaker = new SceneBake(bakeContext);
	m_SceneBaker->Init();

#if MUTITHREAD_SHAREVBO
	m_SceneBaker->InitRenderData(m_SharedVBO);
#else
	m_SceneBaker->InitRenderData();
#endif // MUTITHREAD_SHAREVBO

	while (!glfwWindowShouldClose(bakeContext))
	{
		m_SceneBaker->Tick();

		glfwSwapBuffers(bakeContext);
	}

	glfwMakeContextCurrent(NULL);
	glfwDestroyWindow(bakeContext);

	delete(m_SceneBaker);
}

void Application::ShutDown()
{

}

Application::~Application()
{
}