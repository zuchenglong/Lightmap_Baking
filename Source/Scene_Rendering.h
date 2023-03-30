#pragma once

#include <iostream>
#include <glad/glad.h>

class Scene_Rendering
{
public:
	Scene_Rendering();
	~Scene_Rendering();

	void InitRenderBuffer();

	void InitShaderProgram();
private:

};
