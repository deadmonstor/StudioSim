#pragma once

#include <list>
#include <map>
#include <string>
#include <vector>

#include "shader.h"
#include "texture.h"

class ResourceManager
{
public:
	static Shader    LoadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, std::string name);
	static Shader    GetShader(std::string name);

	static Texture            LoadTexture(const char *file, std::string name);
	static std::list<Texture> LoadTextureArray(const char* folder, const std::string& name, int numTextures);

	static Texture              GetTexture(std::string name);
	static std::vector<Texture> GetTexturesContaining(std::string name);

	static void Clear();
private:
	ResourceManager() = default;
	static Shader    loadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile = nullptr);
	static Texture   loadTextureFromFile(const char *file);

	static std::map<std::string, Shader>    Shaders;
	static std::map<std::string, Texture>   Textures;
};
