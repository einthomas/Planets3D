#include "Light.h"

Light::Light(glm::vec3 pos, Material material, float constant, float linear, float quadratic)
{
	this->pos = pos;
	this->material = material;
	this->constant = constant;
	this->linear = linear;
	this->quadratic = quadratic;
}

Light::Light(glm::vec3 dir, Material material)
{
	this->material = material;
	this->dir = dir;
}

Light::Light(glm::vec3 pos, Material material, glm::vec3 dir, GLfloat innerCutOff, GLfloat outerCutOff, float constant, float linear, float quadratic)
{
	this->pos = pos;
	this->material = material;
	this->dir = dir;
	this->innerCutOff = innerCutOff;
	this->outerCutOff = outerCutOff;
	this->constant = constant;
	this->linear = linear;
	this->quadratic = quadratic;
}
