#include "FlashLight.h"

FlashLight::FlashLight(Camera *camera, Material material, GLfloat innerCutOff, GLfloat outerCutOff, float constant, float linear, float quadratic)
	: SpotLight(camera->pos, material, camera->front, innerCutOff, outerCutOff, constant, linear, quadratic)
{
	this->camera = camera;
	type = LightType::FLASH;
}

void FlashLight::update()
{
	pos = camera->pos;
	dir = camera->front;
}
