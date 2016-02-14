#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(glm::vec3 dir, Material material) : Light(dir, material)
{
	type = LightType::DIRECTIONAL;
}
