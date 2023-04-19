#include "../Define.h"

#include "Model.h"
#include "Camera.h"

Model::Model()
{

}

void Model::SetMeshs(Mesh* mesh)
{
	m_Meshs.push_back(mesh);
}

void Model::Init()
{
	for (auto i : m_Meshs)
	{
		i->InitMeshData();
	}
}

void Model::Show()
{
	if (m_BlinnPhone == nullptr)
	{
		m_BlinnPhone = new Shader(BlinnPhone_VS.c_str(), BlinnPhone_FS.c_str());
	}

	for (auto i : m_Meshs)
	{
		glm::mat4 model = glm::mat4(1.0f);
		glm::translate(model, glm::vec3(0, 0, 1));
		m_BlinnPhone->SetMat4("Model", model);
		m_BlinnPhone->SetMat4("View", Camera::GetMainCamera()->GetViewMatrix());
		m_BlinnPhone->SetMat4("Projection",Camera::GetMainCamera()->GetProjectionMatrix());
		i->Draw(m_BlinnPhone);
	}
}

void Model::Show(Shader* shader)
{
	for (auto i : m_Meshs)
	{
		i->Draw(shader);
	}
}

Model::~Model()
{

}