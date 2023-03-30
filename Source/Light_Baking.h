// Lightmap_Baking.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <glad/glad.h>

// TODO: Reference additional headers your program requires here.

class Light_Baking
{
public:
	Light_Baking();
	~Light_Baking();

	void InitRenderBuffer();

	void InitShaderProgram();
private:

};
