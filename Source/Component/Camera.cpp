#include "Camera.h"

Camera::Camera()
{
	m_Postion = glm::vec3(0.0f, 0.0f, 0.0f);

	m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
	m_Front = glm::vec3(0.0f, 0.0f, 1.0f);

	m_WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);

	m_Yaw = CameraDefine::Yaw;
	m_Pitch = CameraDefine::Pitch;
	m_Zoom = CameraDefine::Zoom;
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(m_Postion, m_Postion + m_Front, m_Up);
}

glm::mat4 Camera::GetProjectionMatrix()
{
	return glm::perspective(glm::radians(m_Zoom), (float)width / (float)height, 0.1f, 100.0f);
}

void Camera::SetCameraFov(float fov)
{
	m_Zoom = fov;
}

void Camera::SetCameraPostion(glm::vec3 postion)
{
	m_Postion = postion;
}

void Camera::SetCameraRotation(glm::vec3 rotation)
{
	m_Pitch = rotation.x;
	m_Yaw = rotation.y;
	m_Row = rotation.z;
}

float Camera::GetCameraFov()
{
	return m_Zoom;
}

glm::vec3 Camera::GetCameraPostion()
{
	return m_Postion;
}

glm::vec3 Camera::GetCameraRotation()
{
	glm::vec3 rotation;

	rotation.x = m_Pitch;
	rotation.y = m_Yaw;
	rotation.z = m_Row;

	return rotation;
}

void Camera::UpdateCameraTransform()
{
	glm::vec3 front;
	front.x = cos(glm::radians(m_Pitch)) * cos(glm::radians(m_Yaw));
	front.y = sin(glm::radians(m_Pitch));
	front.z = cos(glm::radians(m_Pitch)) * sin(glm::radians(m_Yaw));

	m_Front = glm::normalize(front);
	m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
	m_Up = glm::normalize(glm::cross(m_Right, m_Front));
}

Camera::~Camera()
{

}