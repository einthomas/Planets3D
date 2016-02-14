#pragma once

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <iostream>
#include <string>
#include <vector>

#include "Light.h"
#include "FlashLight.h"

class LightManager
{
public:
	static std::vector<Light*> lights;
	static void update(GLfloat dt);
};
