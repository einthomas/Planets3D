#pragma once

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <string>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "Shape.h"
#include "Camera.h"
#include "Shader.h"
#include "LightManager.h"

class Cube : public Shape
{
public:
	Cube(Camera *camera, Shader *shader, glm::vec3 pos, glm::vec3 scale, Material material, GLfloat rotation);
	void update(GLfloat dt);
	void draw();
	GLuint getVAO();
};
