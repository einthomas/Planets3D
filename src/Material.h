#pragma once

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm.hpp>
#include <SOIL.h>
#include "imageloader.h"

class Material
{
public:
	GLfloat shininess;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	GLuint diffuseMap = -1;
	GLuint specularMap = -1;
	GLuint ambientMap = -1;
	Image *heightMap = nullptr;

	Material();
	Material(GLfloat shininess, GLuint diffuseMap, GLuint specularMap);
	Material(GLfloat shininess, GLuint diffuseMap, GLuint specularMap, Image *heightMap);
	Material(GLfloat shininess, GLuint ambientMap, GLuint diffuseMap, GLuint specularMap);
	Material(GLfloat shininess, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
};
