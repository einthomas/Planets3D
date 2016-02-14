#pragma once

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <string>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "Material.h"

enum class LightType
{
	DIRECTIONAL,
	POINT,
	SPOT,
	FLASH
};

class Light
{
public:
	LightType type;
	Material material;
	glm::vec3 pos;

	// Point light
	float constant;
	float linear;
	float quadratic;

	// Directional/Spot light
	glm::vec3 dir;

	// Spot light
	GLfloat innerCutOff;
	GLfloat outerCutOff;

	Light(glm::vec3 pos, Material material, float constant, float linear, float quadratic);				// Point light
	Light(glm::vec3 dir, Material material);															// Directional light
	Light(glm::vec3 pos, Material material, glm::vec3 dir, GLfloat innerCutOff, GLfloat outerCutOff, float constant, float linear, float quadratic);	// Spot light
};
