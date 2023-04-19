#pragma once
#include <map>
#include <iostream>
#include <functional>
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

class Input;
#define GLFW_STATUS_NONE                1000
#define LOG_INPUT_INFO 0

static Input* m_Input;

static std::map<int, int> key_status;
static std::map<int, int> mouse_button_status;
static std::map<int, int> m_pre_key_status;
static std::map<int, int> m_pre_mouse_button_status;

static glm::vec2 m_MousePosition = glm::vec2(0, 0);
static glm::vec2 m_ScrollValue = glm::vec2(0, 0);

class Input
{
public:
	Input();
	~Input();

    static void Init();
	static void Tick();

public:
	static Input* Get()
	{
		if (m_Input == nullptr)
		{
			m_Input = new Input();
		}

		return m_Input;
	}

	void KeyEventCallback(int key, int action);
	void MouseButtonEventCallback(int button, int action);
	void MousePositionCallback(double xposIn, double yposIn);
	void MouseScrollCallback(double xoffset, double yoffset);

	static glm::vec2 GetMousePosition();
	static glm::vec2 GetScrollCallback();

	static bool GetMouseButtonDown(int key);
	static bool GetMouseButton(int key);
	static bool GetMouseButtonUp(int key);

	static bool GetKeyDown(int key);
	static bool GetKey(int key);
	static bool GetKeyUp(int key);
private:
	static void SyncKeyStatus();
};

static void KeyEventCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	std::function<void(int, int)> key_callback = std::bind(&Input::KeyEventCallback, Input::Get(), key, action);
	key_callback(key, action);
}

static void MouseButtonEventCallback(GLFWwindow* window, int button, int action, int mods)
{
	std::function<void(int, int)> mouse_button_callback = std::bind(&Input::MouseButtonEventCallback, Input::Get(), button, action);
	mouse_button_callback(button, action);
}

static void MousePositionCallback(GLFWwindow* window, double xposIn, double yposIn)
{
	std::function<void(int, int)> mouse_position_callback = std::bind(&Input::MousePositionCallback, Input::Get(), xposIn, yposIn);
	mouse_position_callback(xposIn, yposIn);
}

static void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	std::function<void(int, int)> mouse_scroll_callback = std::bind(&Input::MouseScrollCallback, Input::Get(), xoffset, yoffset);
	mouse_scroll_callback(xoffset, yoffset);
}

