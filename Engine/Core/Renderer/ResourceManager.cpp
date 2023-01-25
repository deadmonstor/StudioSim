#include "ResourceManager.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <glad/glad.h>

#include "Util/Logger.h"

#ifndef STB_IMAGE_IMPLEMENTATION
    #define STB_IMAGE_IMPLEMENTATION
    #include "Util/stb_image.h"
#endif

// Instantiate static variables
std::map<std::string, Texture>          ResourceManager::Textures;
std::map<std::string, Shader>           ResourceManager::Shaders;
std::map<std::string, FMOD::Sound*>     ResourceManager::Sounds;

Shader ResourceManager::LoadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, std::string name)
{
    LOG_INFO("Loading shader: " + name);
    
    Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    return Shaders[name];
}

bool ResourceManager::HasShader(const std::string name)
{
    return Shaders.contains(name);
}

Shader ResourceManager::GetShader(const std::string name)
{
    if (!HasShader(name))
    {
        LOG_ERROR("ERROR::SHADER: Failed to find shader with name: " + name);
    }
    
    return Shaders[name];
}

Texture ResourceManager::LoadTexture(const char *file, const std::string name)
{
    Textures[name] = loadTextureFromFile(file);
    return Textures[name];
}

std::list<Texture> ResourceManager::LoadTextureArray(const char* folder,
                                                        const std::string& name,
                                                        const int numTextures)
{
    std::list<Texture> textures;
    
    for (int i = 0; i < numTextures; i++)
    {
        std::string currentString(folder);
        currentString.append(name);
        currentString.append(std::to_string(i));
        currentString.append(".png");

        std::string currentStringID(name);
        currentStringID.append(std::to_string(i));

        textures.push_back(LoadTexture(currentString.c_str(), currentStringID));
    }
    
    return textures;
}

Texture ResourceManager::GetTexture(std::string name)
{
    if (!Textures.contains(name))
    {
        LOG_ERROR("ERROR::TEXTURE: Failed to find texture with name: " + name);
    }
    
    return Textures[name];
}

void ResourceManager::LoadSound(const char *path, FMOD_MODE fMode, FMOD::System *fmodSystem) 
{ 
    FMOD::Sound *fmodSound = nullptr;
	fmodSystem->createSound(path, FMOD_2D, nullptr, &fmodSound);
	Sounds[path] = fmodSound;
}

bool ResourceManager::HasSound(const char *path) 
{
    return Sounds.contains(path);
}

FMOD::Sound *ResourceManager::GetSound(const char *path) 
{
    if (!HasSound(path))
    {
        LOG_ERROR("ERROR::SOUND: Failed to find sound with path: " + std::string(path));
    }
    
    return Sounds[path];
}

std::vector<Texture> ResourceManager::GetTexturesContaining(const std::string name)
{
    std::vector<Texture> textures;
    
    for (auto& [str, texture] : Textures)
    {
        if (str.find(name) == 0)
        {
            textures.push_back(texture);
        }
    }
    
    std::ranges::sort(textures, [](const Texture& a, const Texture& b)
    {
        return a.ID < b.ID;
    });
    
    return textures;
}

void ResourceManager::Clear()
{
    for (const auto& [fst, snd] : Shaders)
        glDeleteProgram(snd.ID);

    for (const auto& [fst, snd] : Textures)
        glDeleteTextures(1, &snd.ID);
}

Shader ResourceManager::loadShaderFromFile(const char* vShaderFile, const char *fShaderFile, const char *gShaderFile)
{
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    try
    {
        // open files
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        
        // if geometry shader path is present, also load a geometry shader
        if (gShaderFile != nullptr)
        {
            std::ifstream geometryShaderFile(gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::exception&)
    {
        LOG_ERROR("ERROR::SHADER: Failed to read shader files");
    }
    
    if (vertexCode.empty())
    {
        std::string errorFile(vShaderFile);
        LOG_ERROR("ERROR::SHADER: Failed to read vertex shader file, file: " + errorFile);
        abort();
    }
    
    if (fragmentCode.empty())
    {
        std::string errorFile(fShaderFile);
        LOG_ERROR("ERROR::SHADER: Failed to read fragment shader file, file: " + errorFile);
        abort();
    }
    
    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();
    const char *gShaderCode = geometryCode.c_str();

    // 2. now create shader object from source code
    Shader shader;
    shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
    return shader;
}

Texture ResourceManager::loadTextureFromFile(const char *file)
{
    Texture texture;
    int width, height, nrChannels;
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);

    if (nrChannels == 4)
    {
        texture.Internal_Format = GL_RGBA;
        texture.Image_Format = GL_RGBA;
    }
        
    if (!stbi_failure_reason())
    {
        texture.Generate(width, height, data);
    }
    else
    {
        LOG_ERROR("ERROR::TEXTURE: Failed to load texture " + std::string(file));
        LOG_ERROR(stbi_failure_reason());
    }

    stbi_image_free(data);
    
    return texture;
}