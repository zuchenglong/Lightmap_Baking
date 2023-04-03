#pragma once
#include <string>
#include <glm/glm.hpp>
#include <direct.h>
#include "glad/glad.h"

using namespace std;

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

public:
	void use();

	void SetBool(const string& name, bool value);
	void SetInt(const string& name, int value) ;
	void SetFloat(const string& name, float value) ;
	void SetVec2(const string& name,const glm::vec2& value);
	void SetVec3(const string& name,const glm::vec3& value);
	void SetVec4(const string& name,const glm::vec4& value);
	void SetMat4(const string& name,const glm::mat4& value);
	void SetTexture(const string& name, int value);
private:
	std::string GetCWD()
	{
		const int MAX_LENGTH = 512;
		char buffer[MAX_LENGTH];

		getcwd(buffer,512);
		std::string cwd = buffer;

		int pos = cwd.find("\\");
		while (pos != cwd.npos)
		{
			cwd.replace(pos,1,"/");
			pos = cwd.find("\\");
		}

		return cwd;
	}
};
