#include <iostream>
#include <glad/glad.h>
#include "shader.h"
#include "glm/gtc/type_ptr.hpp"
#include "Util/Logger.h"

Shader& Shader::Use()
{
	glUseProgram(this->ID);
	return *this;
}

void Shader::Compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource)
{
	const unsigned int sVertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(sVertex, 1, &vertexSource, nullptr);
	glCompileShader(sVertex);
	checkCompileErrors(sVertex, VERTEX_SHADER);

	const unsigned int sFragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(sFragment, 1, &fragmentSource, nullptr);
	glCompileShader(sFragment);
	checkCompileErrors(sFragment, FRAGMENT_SHADER);

	unsigned int gShader = 0;
	if (geometrySource != nullptr)
	{
		gShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(gShader, 1, &geometrySource, nullptr);
		glCompileShader(gShader);
		checkCompileErrors(gShader, GEOMETRY_SHADER);
	}

	this->ID = glCreateProgram();
	glAttachShader(this->ID, sVertex);
	glAttachShader(this->ID, sFragment);
	if (geometrySource != nullptr)
		glAttachShader(this->ID, gShader);

	glLinkProgram(this->ID);
	checkCompileErrors(this->ID, PROGRAM);

	glDeleteShader(sVertex);
	glDeleteShader(sFragment);

	if (geometrySource != nullptr)
		glDeleteShader(gShader);
}

void Shader::SetFloat(const char* name, const float value, const bool useShader)
{
	if (useShader)
		this->Use();

	glUniform1f(glGetUniformLocation(this->ID, name), value);
}

void Shader::SetInteger(const char* name, const int value, const bool useShader)
{
	if (useShader)
		this->Use();

	glUniform1i(glGetUniformLocation(this->ID, name), value);
}

void Shader::SetVector2f(const char* name, const float x, const float y, const bool useShader)
{
	if (useShader)
		this->Use();

	glUniform2f(glGetUniformLocation(this->ID, name), x, y);
}

void Shader::SetVector2f(const char* name, const glm::fvec2& value, const bool useShader)
{
	if (useShader)
		this->Use();

	glUniform2f(glGetUniformLocation(this->ID, name), value.x, value.y);
}

void Shader::SetVector3f(const char* name, const float x, const float y, const float z, const bool useShader)
{
	if (useShader)
		this->Use();

	glUniform3f(glGetUniformLocation(this->ID, name), x, y, z);
}

void Shader::SetVector3f(const char* name, const glm::fvec3& value, const bool useShader)
{
	if (useShader)
		this->Use();

	glUniform3f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z);
}

void Shader::SetVector4f(const char* name, const float x, const float y, const float z, const float w, const bool useShader)
{
	if (useShader)
		this->Use();

	glUniform4f(glGetUniformLocation(this->ID, name), x, y, z, w);
}

void Shader::SetVector4f(const char* name, const glm::fvec4& value, const bool useShader)
{
	if (useShader)
		this->Use();

	glUniform4f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z, value.w);
}

void Shader::SetMatrix4(const char* name, const glm::mat4& matrix, const bool useShader)
{
	if (useShader)
		this->Use();

	glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, false, value_ptr(matrix));
}

void Shader::checkCompileErrors(const unsigned int object, const ShaderType type)
{
	int success;

	if (type == PROGRAM)
		glGetProgramiv(object, GL_LINK_STATUS, &success);
	else
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);
	
	if (success)
	{
		return;
	}
	
	char infoLog[1024];
		
	glGetProgramInfoLog(object, 1024, nullptr, infoLog);
	std::string errorLog = "ERROR::SHADER: ";
	errorLog.append(type == PROGRAM ? "Link-time error" : "Compile-time error");
	errorLog.append(": Type: ");
	errorLog.append(type == VERTEX_SHADER ? "VERTEX" : type == FRAGMENT_SHADER ? "FRAGMENT" : "GEOMETRY");
	errorLog.append("\n");
	errorLog.append(infoLog);
	
	LOG_ERROR(errorLog);
}
