#include "Shader.h"

#include <iostream>

Shader::Shader() { }

Shader::Shader(const GLchar* vertexSource, const GLchar* fragmentSource) {
	GLuint vertexShader = loadShader(GL_VERTEX_SHADER, vertexSource);
	GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentSource);

	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADERPROGRAM::LINKING\n" << infoLog << std::endl;
	}
}

void Shader::use() {
	glUseProgram(program);
}

GLuint Shader::loadShader(GLuint shaderType, const GLchar* shaderCode) {
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderCode, NULL);
	glCompileShader(shader);

	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return shader;
}

void Shader::setFloat(const GLchar *name, GLfloat value) {
	glUniform1f(glGetUniformLocation(program, name), value);
}

void Shader::setInteger(const GLchar *name, GLint value) {
	glUniform1i(glGetUniformLocation(program, name), value);
}

void Shader::setVector2f(const GLchar *name, GLfloat x, GLfloat y) {
	glUniform2f(glGetUniformLocation(program, name), x, y);
}

void Shader::setVector2f(const GLchar *name, glm::vec2 value) {
	glUniform2f(glGetUniformLocation(program, name), value.x, value.y);
}

void Shader::setVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z) {
	glUniform3f(glGetUniformLocation(program, name), x, y, z);
}

void Shader::setVector3f(const GLchar *name, glm::vec3 value) {
	glUniform3f(glGetUniformLocation(program, name), value.x, value.y, value.z);
}

void Shader::setMatrix4(const GLchar *name, const glm::mat4 &value) {
	glUniformMatrix4fv(glGetUniformLocation(program, name), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setTexture2D(const GLchar *name, GLenum activeTexture, GLuint texture, GLuint loc) {
	glActiveTexture(activeTexture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(program, name), loc);
}
