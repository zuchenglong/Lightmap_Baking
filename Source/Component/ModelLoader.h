#pragma once

#ifndef COMPONENT_MODEL
#define COMPONENT_MODEL

#include "Mesh.h"
#include "Shader.h"

#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include "Model.h"

class ModelLoader;

static ModelLoader* modelLoader;

class ModelLoader
{
public:
	static ModelLoader* Get()
	{
		if (modelLoader == nullptr)
		{
			modelLoader = new ModelLoader();
		}

		return modelLoader;
	}

	ModelLoader();
	void LoadModel(std::string path, Model* model);
	void Show(Shader* shader);

	~ModelLoader();

public:
	vector<Texture> textures_loaded;

private:
	string m_Directory;

private:
	void ProcessNode(aiNode* aiNode, const aiScene* scene, Model* model);
	Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> LoadMaterialTexture(aiMaterial* mat, aiTextureType type, string typeName);
};

#endif