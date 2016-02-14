#pragma once

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <string>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "ResourceManager.h"
#include "Quad.h"

class Screen
{
public:
	Screen(GLuint width, GLuint height);
	void beginDraw();
	void endDraw();

private:
	GLuint framebuffer;
	GLuint texColorBuffer;
	Quad *screenQuad;
};
