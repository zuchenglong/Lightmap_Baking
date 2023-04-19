#include <string>
#include <vector>

class TextureLoader;

static TextureLoader* textureLoader;

class TextureLoader
{
public:
	
	static TextureLoader* Get()
	{
		if (textureLoader == nullptr)
		{
			textureLoader = new TextureLoader();
		}

		return textureLoader;
	}

	unsigned int LoadTextureFromFile(const char* path,const std::string& directory);
	unsigned int LoadCubeMap(std::vector<std::string> faces);
private:

private:
	TextureLoader();

	//保证安全性
	TextureLoader(const TextureLoader&) = delete;
	TextureLoader& operator = (const TextureLoader&) = delete;

	~TextureLoader();

};
