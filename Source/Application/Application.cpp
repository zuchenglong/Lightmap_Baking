#include "Application.h"


Application::Application()
{
}

void Application::Init()
{
	CameraController::Get()->Init();
}

void Application::Tick()
{
	CameraController::Get()->Tick();
}

Application::~Application()
{
}