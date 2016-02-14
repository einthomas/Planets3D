#pragma once

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <string>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "SpotLight.h"
#include "Material.h"
#include "Camera.h"

class FlashLight : public SpotLight
{
public:
	FlashLight(Camera *camera, Material material, GLfloat innerCutOff, GLfloat outerCutOff, float constant, float linear, float quadratic);
	void update();

private:
	Camera *camera;
};
