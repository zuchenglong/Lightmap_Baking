#pragma once

#include <string>

// 是否开启 烘焙线程
#define ENABLE_BAKETHREAD 1
// 是否多线程 共享VBO
#define MUTITHREAD_SHAREVBO 1
// 主线程 画面是否上屏
#define DRAW_SCREEN_MAINTHREAD 1
// 烘焙线程 画面是否上屏
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

	//初始默认值
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

