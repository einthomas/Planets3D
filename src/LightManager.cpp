#include "LightManager.h"

std::vector<Light*> LightManager::lights;

void LightManager::update(GLfloat dt)
{
	for (GLuint i = 0; i < lights.size(); i++)
		if (LightManager::lights[i]->type == LightType::FLASH)
			((FlashLight*)LightManager::lights[i])->update();
}
