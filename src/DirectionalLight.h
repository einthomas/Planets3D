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

class DirectionalLight : public Light
{
public:
	DirectionalLight(glm::vec3 dir, Material material);
};
