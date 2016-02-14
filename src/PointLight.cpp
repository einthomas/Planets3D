#include "PointLight.h"

PointLight::PointLight(glm::vec3 pos, Material material, float constant, float linear, float quadratic)
	: Light(pos, material, constant, linear, quadratic)
{
	type = LightType::POINT;
}
