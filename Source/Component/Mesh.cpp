#include "Mesh.h"

Mesh::Mesh(const Mesh& mesh)
{
	this->m_Vertices = mesh.m_Vertices;
	this->m_Indices = mesh.m_Indices;
	this->m_Textures = mesh.m_Textures;
}

Mesh::Mesh(vector<Vertex> vertices,vector<unsigned int> indices,vector<Texture> textures)
{
	this->m_Vertices = vertices;
	this->m_Indices = indices;
	this->m_Textures = textures;
}

void Mesh::InitMeshData()
{
	//绑定缓冲
	glGenVertexArrays(1,&VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1,&EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(m_Vertices), &m_Vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,m_Indices.size() * sizeof(unsigned int), &m_Indices[0],GL_STATIC_DRAW);

	//数据解析
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex,Normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex,TexCoords));

	glBindVertexArray(0);
}


void Mesh::Draw(Shader* shader)
{
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;

	for (unsigned int i = 0; i < m_Textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		string number;
		string type =m_Textures[i].type;

		if (type == "texture_diffuse")
		{
			number = std::to_string(diffuseNr++);
		}
		else if (type == "texture_specular")
		{
			number = std::to_string(specularNr++);
		}
		else if (type == "texture_normal")
		{
			number = std::to_string(normalNr++);
		}
		else if (type == "texture_height")
		{
			number = std::to_string(heightNr++);
		}

		shader->SetTexture(type + number, i);
		glBindTexture(GL_TEXTURE_2D, m_Textures[i].id);
	}

	glActiveTexture(GL_TEXTURE0);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(m_Indices.size()), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1,&VAO);
	glDeleteBuffers(1,&VBO);
}
