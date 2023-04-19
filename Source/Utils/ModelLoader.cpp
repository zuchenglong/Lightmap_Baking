#include "ModelLoader.h"
#include "TextureLoader.h"
#include <iostream>

ModelLoader::ModelLoader()
{

}


void ModelLoader::LoadModel(std::string path, Model* model)
{
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
		return;
	}
	m_Directory = path.substr(0, path.find_last_of('/'));
	ProcessNode(scene->mRootNode, scene, model);
}

void ModelLoader::ProcessNode(aiNode* node, const aiScene* scene, Model* model)
{
	//遍历节点下Mesh
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		//通过索引获取Scene下Mesh
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		model->SetMeshs(ProcessMesh(mesh, scene));
	}

	//继续遍历子节点
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene, model);
	}
}

//提取 vertices indices textures
Mesh* ModelLoader::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;

		//获取Mesh的Postion
		glm::vec3 vector;
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Postion = vector;

		//获取Mesh的Normal
		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.Normal = vector;

		if (mesh->mTextureCoords != nullptr && mesh->mTextureCoords[0])
		{
			//获取Mesh的UV坐标
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
		}
		else
		{
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);
		}
		vertices.push_back(vertex);
	}

	//填充includes
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		vector<Texture> diffuseMaps = LoadMaterialTexture(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		vector<Texture> specularMaps = LoadMaterialTexture(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

		vector<Texture> normalMaps = LoadMaterialTexture(material, aiTextureType_HEIGHT, "texture_normal");
		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

		vector<Texture> heightMaps = LoadMaterialTexture(material, aiTextureType_AMBIENT, "texture_height");
		textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
	}

	return new Mesh(vertices, indices, textures);
}

vector<Texture> ModelLoader::LoadMaterialTexture(aiMaterial* mat, aiTextureType type, string typeName)
{
	vector<Texture> textures;
	//遍历所有贴图
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString name;
		//type index path
		mat->GetTexture(type, i, &name);
		bool isSkip = false;
		//判断是否已加载
		for (unsigned int j = 0; j < textures_loaded.size(); j++)
		{
			if (std::strcmp(textures_loaded[j].path.data(), name.C_Str()) == 0)
			{
				textures.push_back(textures_loaded[j]);
				isSkip = true;
				break;
			}
		}
		if (!isSkip)
		{
			Texture texture;
			texture.id = TextureLoader::Get()->LoadTextureFromFile(name.C_Str(), this->m_Directory);
			texture.type = typeName;
			texture.path = name.C_Str();
			textures.push_back(texture);
			textures_loaded.push_back(texture);
		}
	}
	return textures;
}

ModelLoader::~ModelLoader()
{

}