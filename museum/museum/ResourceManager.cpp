#include "ResourceManager.h"

#include <iostream>
#include <stb_image.h>



// Instantiate static variables
std::map<std::string, Texture2D>    ResourceManager::Textures;
std::map<std::string, Shader>       ResourceManager::Shaders;


Shader ResourceManager::LoadShader(const std::string& vShaderFile, const std::string& fShaderFile, std::string name)
{
	Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile);
	return Shaders[name];
}

Shader& ResourceManager::GetShader(std::string name)
{
	return Shaders[name];
}

Texture2D ResourceManager::LoadTexture(const std::string& file, std::string name)
{
	Textures[name] = loadTextureFromFile(file);
	return Textures[name];
}

Texture2D& ResourceManager::GetTexture(std::string name)
{
	return Textures[name];
}


void ResourceManager::Clear()
{
	// (Properly) delete all shaders	
	for (auto iter : Shaders)
		glDeleteProgram(iter.second.GetID());
	// (Properly) delete all textures
	for (auto iter : Textures)
		glDeleteTextures(1, &iter.second.ID);
}

Shader ResourceManager::loadShaderFromFile(const std::string& vShaderFile, const std::string& fShaderFile)
{
	// 1. Retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	try
	{
		// Open files
		std::ifstream vertexShaderFile(vShaderFile);
		std::ifstream fragmentShaderFile(fShaderFile);
		std::stringstream vShaderStream, fShaderStream;
		// Read file's buffer contents into streams
		vShaderStream << vertexShaderFile.rdbuf();
		fShaderStream << fragmentShaderFile.rdbuf();
		// close file handlers
		vertexShaderFile.close();
		fragmentShaderFile.close();
		// Convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::exception e)
	{
		std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	// 2. Now create shader object from source code
	Shader shader;
	shader.Init(vShaderCode, fShaderCode);
	return shader;
}

Texture2D ResourceManager::loadTextureFromFile(const std::string& file)
{
	// Create Texture object
	Texture2D texture;

	int width, height, nrChannels;
	unsigned char* data = stbi_load(file.c_str(), &width, &height, &nrChannels, 0);
	if (data) {
		GLenum format;
		if (nrChannels == 1)
			texture.Image_Format = GL_RED;
		else if (nrChannels == 3)
			texture.Image_Format = GL_RGB;
		else if (nrChannels == 4)
			texture.Image_Format = GL_RGBA;
		// Now generate texture
		texture.Generate(width, height, data);
	}
	else {
		std::cout << "Failed to load texture: " << std::endl;
	}
	// And finally free image data
	stbi_image_free(data);
	return texture;
}
