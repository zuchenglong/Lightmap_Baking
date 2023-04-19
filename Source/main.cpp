#include <glad/glad.h>
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>

#include "Define.h"
#include "Core/Time.h"
#include "Core/Input.h"

#include "Application/Application.h"

using namespace std;

int main()
{
	cout << "Hello CMake." << endl;
	glfwInit();

	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//�������汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//���ôΰ汾��
	GLFWwindow* window = glfwCreateWindow(width, height, "LightmapBaking", NULL, NULL);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//ʹ�ú���ģʽ

#pragma region Input Callback
	glfwSetKeyCallback(window, KeyEventCallback);
	glfwSetMouseButtonCallback(window, MouseButtonEventCallback);
	glfwSetScrollCallback(window, MouseScrollCallback);
	glfwSetCursorPosCallback(window, MousePositionCallback);
#pragma endregion

#if !DRAW_SCREEN_BAKETHREAD
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
#endif // DRAW_SCREEN_BAKETHREAD

	glfwMakeContextCurrent(window);

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1);

	Input::Init();
	Time::Init();

	Application::Get()->Init(window);

	while (!glfwWindowShouldClose(window))	//����Ⱦ�߳�
	{
		Input::Tick();
		Time::Tick();

		Application::Get()->Tick();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwMakeContextCurrent(NULL);
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

