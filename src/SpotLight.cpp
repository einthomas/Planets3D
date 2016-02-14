#include "SpotLight.h"

SpotLight::SpotLight(glm::vec3 pos, Material material, glm::vec3 dir, GLfloat innerCutOff, GLfloat outerCutOff, float constant, float linear, float quadratic)
	: Light(pos, material, dir, innerCutOff, outerCutOff, constant, linear, quadratic)
{
	type = LightType::SPOT;
}
