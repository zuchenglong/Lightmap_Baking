#pragma once

#include <string>

// �Ƿ��� �決�߳�
#define ENABLE_BAKETHREAD 1
// �Ƿ���߳� ����VBO
#define MUTITHREAD_SHAREVBO 1
// ���߳� �����Ƿ�����
#define DRAW_SCREEN_MAINTHREAD 1
// �決�߳� �����Ƿ�����
#define DRAW_SCREEN_BAKETHREAD 0

const unsigned int width = 800, height = 600;

#pragma region FilePath
static std::string ProjectDir(PROJECT_DIR);
static std::string ProjectAssetsDir(PROJECT_ASSETS_DIR);
#pragma endregion

#pragma region Camera
namespace CameraDefine
{
	enum Axis
	{
		x,
		y,
		z
	};

	//��ʼĬ��ֵ
	const float Yaw = -90.0f;
	const float Pitch = 0.0f;
	const float Row = 0.0f;

	const float Speed = 20.0f;
	const float Sensitivity = 10.0f;
	const float Zoom = 45.0f;
}
#pragma endregion

#pragma region Shader
static std::string BlinnPhone_VS(ProjectAssetsDir + "/Shaders/Blinn_Phong.vs");
static std::string BlinnPhone_FS(ProjectAssetsDir + "/Shaders/Blinn_Phong.fs");
#pragma endregion

