#include "Material.h"

Material::Material(Shader* shader)
{
	m_Shader = shader;
}

void Material::SetDiffuse(glm::vec3 diffuse)
{
	m_Diffuse = diffuse;
}

void Material::SetAmbient(glm::vec3 ambient)
{
	m_Ambient = ambient;
}

void Material::SetSpecular(glm::vec3 specular)
{
	m_Specular = specular;
}

void Material::SetSpecularIntensity(float specularIntensity)
{
	m_SpecularIntensity = specularIntensity;
	m_Shader->SetFloat("material.specularIntensity", specularIntensity);
}

Material::~Material()
{
	delete m_Shader;
}