#ifndef SHADER_H
#define SHADER_H
#include <stdlib.h>
#include <GL/glew.h>
#include <GLM.hpp>
#include <glfw3.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class Shader
{
public:
	Shader() = default;
	// constructor generates the shader on the fly
	// ------------------------------------------------------------------------
	Shader(const char* vertexPath, const char* fragmentPath);
	// activate the shader
	// ------------------------------------------------------------------------
	Shader& Use();

	unsigned int GetID() const;

	// MVP
	unsigned int loc_model_matrix;
	unsigned int loc_view_matrix;
	unsigned int loc_projection_matrix;

	// utility uniform functions
	void SetInt(const std::string& name, int value);
	void SetFloat(const std::string& name, const float& value);
	void SetVec3(const std::string& name, const glm::vec3& value);
	void SetVec3(const std::string& name, float x, float y, float z);
	void SetMat4(const std::string& name, const glm::mat4& mat);
	void Init(const char* vertexSource, const char* fragmentSource);


private:
	// utility function for checking shader compilation/linking errors.
	// ------------------------------------------------------------------------
	void CheckCompileErrors(unsigned int shader, std::string type);

private:
	unsigned int ID;
};
#endif

