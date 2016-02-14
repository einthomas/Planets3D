#pragma once

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <string>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "Shader.h"
#include "Material.h"
#include "Camera.h"

class GraphicsObject
{
public:
	glm::vec3 pos;
	glm::vec3 scale;
	glm::vec3 color;
	Material material;
	GLuint texture;
	GLfloat rotation;

	GraphicsObject();
	virtual void update(GLfloat dt) = 0;
	virtual void draw() = 0;

protected:
	GLuint VAO;
	Shader *shader;
	Camera *camera;
	bool staticPos;
};
