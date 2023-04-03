#include "Shader.h"
#include "glm/glm.hpp"

class Material
{
public:
	Material(Shader*);
	~Material();

	void SetDiffuse(glm::vec3);
    void SetSpecular(glm::vec3);
	void SetAmbient(glm::vec3);
	void SetSpecularIntensity(float specularIntensity);

public:
	Shader* m_Shader = nullptr;

	glm::vec3 m_Diffuse;
	glm::vec3 m_Specular;
	glm::vec3 m_Ambient;
	float m_SpecularIntensity;
private:

};
