#pragma once

#include <string>
#include <vector>
#include "Shader.h"
#include "glm/glm.hpp"
#include "glad/glad.h"

using namespace std;

#define MAX_BONE_INFLUENCE 4

struct Vertex
{
	glm::vec3 Postion;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture
{
	unsigned int id;
	string type;
	string path;
};

class Mesh
{
public:
	Mesh(const Mesh&);
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
	~Mesh();

	void InitMeshData();
	void Draw(Shader* shader);
public:
	vector<Vertex> m_Vertices;
	vector<unsigned int> m_Indices;

	vector<Texture> m_Textures;

private:
	unsigned int VAO, VBO, EBO;
};
