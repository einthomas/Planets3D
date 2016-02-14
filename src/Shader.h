#pragma once

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>

#include <string>

class Shader {
public:
	GLuint program;

	Shader();
	Shader(const GLchar* vertexSource, const GLchar* fragmentSource);
	void use();

	void setFloat(const GLchar *name, GLfloat value);
	void setInteger(const GLchar *name, GLint value);
	void setVector2f(const GLchar *name, GLfloat x, GLfloat y);
	void setVector2f(const GLchar *name, glm::vec2 value);
	void setVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z);
	void setVector3f(const GLchar *name, glm::vec3 value);
	void setMatrix4(const GLchar *name, const glm::mat4 &value);
	void setTexture2D(const GLchar *name, GLenum activeTexture, GLuint texture, GLuint loc);

private:
	GLuint loadShader(GLuint shaderType, const GLchar* shaderCode);
};
