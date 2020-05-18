#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <vector>
#include <string>

#include <GL/glew.h>

#include "Texture2D.h"
#include "Shader.h"

class ResourceManager
{
public:
    // Resource storage
    static std::map<std::string, Shader>    Shaders;
    static std::map<std::string, Texture2D> Textures;
    // Loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code. If gShaderFile is not nullptr, it also loads a geometry shader
    static Shader  LoadShader(const std::string& vShaderFile, const std::string& fShaderFile, std::string name);
    // Retrieves a stored sader
    static Shader& GetShader(std::string name);
    // Loads (and generates) a texture from file
    static Texture2D LoadTexture(const std::string& file, std::string name);
    // Retrieves a stored texture
    static Texture2D& GetTexture(std::string name);

    // Properly de-allocates all loaded resources
    static void      Clear();
private:
    // Private constructor, that is we do not want any actual resource manager objects. Its members and functions should be publicly available (static).
    ResourceManager() { }
    // Loads and generates a shader from file
    static Shader    loadShaderFromFile(const std::string& vShaderFile, const std::string& fShaderFile);
    // Loads a single texture from file
    static Texture2D loadTextureFromFile(const std::string& file);
};

#endif

