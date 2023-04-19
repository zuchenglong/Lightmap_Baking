#include "Input.h"

Input::Input()
{

}

void Input::Init()
{
	SyncKeyStatus();
}

void Input::Tick()
{
	for (std::map<int, int>::iterator key_status_iterator = key_status.begin(); key_status_iterator != key_status.end(); ++key_status_iterator)
	{
		if (m_pre_key_status[key_status_iterator->first] == GLFW_RELEASE)
		{
			key_status_iterator->second = GLFW_STATUS_NONE;
		}
	}

	for (std::map<int, int>::iterator mouse_button_status_iterator = mouse_button_status.begin(); mouse_button_status_iterator != mouse_button_status.end(); ++mouse_button_status_iterator)
	{
		if (m_pre_mouse_button_status[mouse_button_status_iterator->first] == GLFW_RELEASE)
		{
			mouse_button_status_iterator->second = GLFW_STATUS_NONE;
		}
	}
}

void Input::SyncKeyStatus()
{
	//Sync Key Status
	for (std::map<int, int>::iterator key_status_iterator = key_status.begin(); key_status_iterator != key_status.end(); ++key_status_iterator)
	{
		m_pre_key_status[key_status_iterator->first] = key_status_iterator->second;
	}
}

glm::vec2 Input::GetMousePosition()
{
	return m_MousePosition;
}

glm::vec2 Input::GetScrollCallback()
{
	return m_ScrollValue;
}

bool Input::GetMouseButtonDown(int key)
{
	return mouse_button_status[key] == GLFW_PRESS;
}

bool Input::GetMouseButton(int key)
{
	return mouse_button_status[key] == GLFW_REPEAT;
}

bool Input::GetMouseButtonUp(int key)
{
	return mouse_button_status[key] == GLFW_RELEASE;
}


bool Input::GetKeyDown(int key)
{
	return key_status[key] == GLFW_PRESS;
}

bool Input::GetKey(int key)
{
	return key_status[key] == GLFW_REPEAT;
}

bool Input::GetKeyUp(int key)
{
	return key_status[key] == GLFW_RELEASE;
}

void Input::KeyEventCallback(int key, int action)
{
#if LOG_INPUT_INFO
	std::cout << "key" << key << "action" << action << std::endl;
#endif // LOG_INPUT_INFO

	if (key_status.count(key))
	{
		key_status[key] = action;
	}
	else
	{
		key_status.insert(std::pair<int, int>(key, action));
	}
}

void Input::MouseButtonEventCallback(int button, int action)
{
#if LOG_INPUT_INFO
	std::cout << "button=" << button << " action=" << action << std::endl;
#endif
	if (mouse_button_status.count(button))
	{
		mouse_button_status[button] = action;
	}
	else
	{
		mouse_button_status.insert(std::pair<int, int>(button, action));
	}
}

void Input::MousePositionCallback(double xposIn, double yposIn)
{
#if LOG_INPUT_INFO
	std::cout << "xposIn=" << xposIn << " yposIn=" << yposIn << std::endl;
#endif
	m_MousePosition = glm::vec2(xposIn, yposIn);
}

void Input::MouseScrollCallback(double xoffset, double yoffset)
{
#if LOG_INPUT_INFO
	std::cout << "xoffset=" << xoffset << " yoffset=" << yoffset << std::endl;
#endif
	m_ScrollValue = glm::vec2(xoffset, yoffset);
}


Input::~Input()
{

}