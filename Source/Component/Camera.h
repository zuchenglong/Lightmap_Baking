#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "../Define.h"

class Camera;

static Camera* camera;

class Camera
{
public:
	static Camera* Get()
	{
		if (camera == nullptr)
		{
			camera = new Camera();
		}

		return camera;
	}

	Camera();
	virtual ~Camera();

	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();

	glm::vec3 GetCameraRotation();
	float GetCameraFov();
	glm::vec3 GetCameraPostion();

	void SetCameraFov(float);
	void UpdateCameraTransform();
	void SetCameraPostion(glm::vec3);
	void SetCameraRotation(glm::vec3);
private:
	glm::vec3 m_Postion;

	glm::vec3 m_Front;
	glm::vec3 m_Up;
	glm::vec3 m_Right;

	glm::vec3 m_WorldUp;

	//EularAngles
	float m_Yaw;
	float m_Pitch;
	float m_Row;

	//CameraAttributes
	float m_MovementSpeed = CameraDefine::Speed;
	float m_MouseSensitivity = CameraDefine::Sensitivity;
	float m_Zoom = CameraDefine::Zoom;
};
