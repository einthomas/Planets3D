#pragma once

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <string>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "GraphicsObject.h"
#include "Camera.h"
#include "Shader.h"
#include "LightManager.h"

class Shape : public GraphicsObject
{
public:
	Shape(GLuint VAO, Camera *camera, Shader *shader, glm::vec3 pos, glm::vec3 scale, Material material, GLfloat rotation);
	Shape(GLuint VAO, Shader *shader, glm::vec3 pos, glm::vec3 scale, GLuint texture, GLfloat rotation, GLboolean staticPos);
	virtual void update(GLfloat dt) = 0;
	virtual void draw();
	virtual GLuint getVAO() = 0;
};
