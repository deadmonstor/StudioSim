#pragma once
#include <list>
#include <map>
#include <string>
#include <vector>
#include "Util/Audio/inc/fmod.hpp"
#include "Util/Audio/inc/fmod_common.h"

#include "shader.h"
#include "texture.h"

class ResourceManager
{
public:

	static Shader    LoadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, std::string name);
	static bool		 HasShader(std::string name);
	static Shader    GetShader(std::string name);

	static Texture            LoadTexture(const char *file, std::string name);
	static std::list<Texture> LoadTextureArray(const char* folder, const std::string& name, int numTextures);

	static Texture              GetTexture(std::string name);
	static std::vector<Texture> GetTexturesContaining(std::string name);
	
	// load a sound using the passed in fmod system
	static void LoadSound(const char *path, FMOD_MODE fMode, FMOD::System *fmodSystem);
	static bool HasSound(const char* path);
	// retrieve a stored sound to play in the audio engine
	static FMOD::Sound *GetSound(const char *path);
	static void Clear();
private:
	ResourceManager() = default;
	static Shader    loadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile = nullptr);
	static Texture   loadTextureFromFile(const char *file);

	static std::map<std::string, Shader>		Shaders;
	static std::map<std::string, Texture>		Textures;
	static std::map<std::string, FMOD::Sound*>  Sounds;
};
