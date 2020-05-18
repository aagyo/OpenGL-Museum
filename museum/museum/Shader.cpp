#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	Init(vertexPath, fragmentPath);
}

Shader& Shader::Use()
{
	glUseProgram(this->ID);
	return *this;
}

unsigned int Shader::GetID() const
{
	return this->ID;
}

void Shader::SetInt(const std::string& name, int value)
{
	glUniform1i(glGetUniformLocation(this->ID, name.c_str()), value);
}

void Shader::SetFloat(const std::string& name, const float& value)
{
	glUniform1f(glGetUniformLocation(this->ID, name.c_str()), value);
}

void Shader::SetVec3(const std::string& name, const glm::vec3& value)
{
	glUniform3fv(glGetUniformLocation(this->ID, name.c_str()), 1, &value[0]);
}

void Shader::SetVec3(const std::string& name, float x, float y, float z)
{
	glUniform3f(glGetUniformLocation(this->ID, name.c_str()), x, y, z);
}

void Shader::SetMat4(const std::string& name, const glm::mat4& mat)
{
	glUniformMatrix4fv(glGetUniformLocation(this->ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::Init(const char* vertexSource, const char* fragmentSource)
{
	unsigned int sVertex, sFragment, gShader;
	// Vertex Shader
	sVertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(sVertex, 1, &vertexSource, NULL);
	glCompileShader(sVertex);
	CheckCompileErrors(sVertex, "VERTEX");
	// Fragment Shader
	sFragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(sFragment, 1, &fragmentSource, NULL);
	glCompileShader(sFragment);
	CheckCompileErrors(sFragment, "FRAGMENT");
	// Shader Program
	this->ID = glCreateProgram();
	glAttachShader(this->ID, sVertex);
	glAttachShader(this->ID, sFragment);
	glLinkProgram(this->ID);
	CheckCompileErrors(this->ID, "PROGRAM");
	// Delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(sVertex);
	glDeleteShader(sFragment);
}

void Shader::CheckCompileErrors(unsigned int shader, std::string type)
{
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else {
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}
