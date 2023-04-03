#pragma once

#include <vector>

#include "Mesh.h"

using namespace std;

class Model
{
public:
	Model();
	~Model();

	void Init();

	void Show();
	void Show(Shader* shader);
	void SetMeshs(Mesh* mesh);
private:
	Shader* m_BlinnPhone = nullptr;
	vector<Mesh*> m_Meshs;
};

