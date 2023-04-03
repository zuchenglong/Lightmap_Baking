#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>

unsigned int ID;

Shader::Shader(const char* vertexPath,const char* fragmentPath)
{
	std::string dir = GetCWD();

	string vertexCode;
	string fragmentCode;

	ifstream vShaderStream;
	ifstream fShaderStream;

	vShaderStream.exceptions(ifstream::failbit | ifstream::badbit);
	fShaderStream.exceptions(ifstream::failbit | ifstream::badbit);

	try
	{
		vShaderStream.open(vertexPath);
		fShaderStream.open(fragmentPath);

		stringstream vStringStream, fStringStream;
		vStringStream << vShaderStream.rdbuf();
		fStringStream << fShaderStream.rdbuf();

		vShaderStream.close();
		fShaderStream.close();

		vertexCode = vStringStream.str();
		fragmentCode = fStringStream.str();
	}
	catch (const std::exception&)
	{
		std::cout << "Open Shader File Fail！！！" << endl;
	}

	//读取完毕
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	//创建 Shader
	unsigned int vertex, fragment;
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);

	GLint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram,vertex);
	glAttachShader(shaderProgram, fragment);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
	
	//创建 Programe
	ID = glCreateProgram();
	glAttachShader(ID,vertex);
	glAttachShader(ID,fragment);
	glLinkProgram(ID);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::SetBool(const string& name, bool value)
{
	glUniform1i(glGetUniformLocation(ID,name.c_str()),(int)value);
}

void Shader::SetInt(const string& name, int value)
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::SetFloat(const string& name,const float value)
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::SetVec2(const string& name,const glm::vec2& value)
{
	glUniform2f(glGetUniformLocation(ID, name.c_str()), value.x,value.y);
}

void Shader::SetVec3(const string& name,const glm::vec3& value)
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), value.x, value.y,value.z);
}

void Shader::SetVec4(const string& name, const glm::vec4& value)
{
	glUniform4f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z,value.w);
}

void Shader::SetMat4(const string& name,const glm::mat4& value)
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()),1,GL_FALSE,&value[0][0]);
}

void Shader::SetTexture(const string& name, int value)
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

Shader::~Shader()
{
	glDeleteProgram(ID);
}