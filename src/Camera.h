#pragma once

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <GL\glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <iostream>
#include <string>
#include <fstream>

#include "Movement.h"

class Camera
{
public:
	glm::vec3 pos;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 worldUp;

	const GLfloat SPEED = 4.0f;

	GLfloat yaw = 0.0f;
	GLfloat pitch = 0.0f;

	Camera();
	Camera(glm::vec3 pos);
	glm::mat4 getViewMatrix();
	void handleKeyboardInput(Movement movement, GLfloat deltaTime);
	void handleMouseInput(GLfloat offsetX, GLfloat offsetY);
};
