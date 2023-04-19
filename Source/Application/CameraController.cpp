#include "Core/Input.h"
#include "Core/Time.h"
#include "CameraController.h"
#include "Component/Camera.h"


CameraController::CameraController()
{

}

void CameraController::Init()
{
	m_MainCamera = Camera::GetMainCamera();
}

void CameraController::Tick()
{
	float deltaTime = Time::GetDeltaTime();

	glm::vec3 pos = m_MainCamera->GetCameraPostion();

	if (Input::Get()->GetKey(GLFW_KEY_W))
	{
		std::cout << "W Down" << std::endl;
		pos += glm::vec3(Time::GetDeltaTime(), 0,0);
	}
	else if (Input::Get()->GetKey(GLFW_KEY_S))
	{
		std::cout << "S Down" << std::endl;
		pos += glm::vec3(-Time::GetDeltaTime(), 0, 0);
	}
	else if (Input::Get()->GetKey(GLFW_KEY_A))
	{
		std::cout << "A Down" << std::endl;
		pos += glm::vec3(0, 0 ,-Time::GetDeltaTime());
	}
	else if (Input::Get()->GetKey(GLFW_KEY_D))
	{
		std::cout << "D Down" << std::endl;
		pos += glm::vec3(0, 0, Time::GetDeltaTime());
	}
	else if (Input::Get()->GetKey(GLFW_KEY_Q))
	{
		std::cout << "Q Down" << std::endl;
		pos += glm::vec3(0, Time::GetDeltaTime(), 0);
	}
	else if (Input::Get()->GetKey(GLFW_KEY_E))
	{
		std::cout << "E Down" << std::endl;
		pos += glm::vec3(0, -Time::GetDeltaTime(), 0);
	}
	m_MainCamera->SetCameraPostion(pos);
	std::cout << "CameraPosition=(" << std::to_string(pos.x) << "," << std::to_string(pos.y) << "," << std::to_string(pos.z) << ")" << std::endl;
}


CameraController::~CameraController()
{

}