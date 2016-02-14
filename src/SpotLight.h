#pragma once

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <string>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "Light.h"
#include "Material.h"

class SpotLight : public Light
{
public:
	SpotLight(glm::vec3 pos, Material material, glm::vec3 dir, GLfloat innerCutOff, GLfloat outerCutOff, float constant, float linear, float quadratic);
};
