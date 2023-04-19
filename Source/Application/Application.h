#include <thread>
#include "CameraController.h"

#include "Application/Renderer/SceneBake.h"
#include "Application/Renderer/SceneRenderer.h"

extern class Application;
static Application* m_Application = nullptr;

class Application
{
public:
	Application();
	~Application();

    static Application* Get()
	{
		if (m_Application == nullptr)
		{
			m_Application = new Application();
		}

		return m_Application;
	}

	void Init(GLFWwindow*);
	void Tick();
	void ShutDown();
private:
	void InitSharingVertexBuffers();
	void InitBakeThread(GLFWwindow* bakeContext);

	SceneRenderer* m_SceneRenderer = nullptr;
	SceneBake* m_SceneBaker = nullptr;

	GLuint m_SharedVBO;

	std::thread m_BakeThread;
};
