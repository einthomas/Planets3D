#pragma once

#include "ResourceManager.h"
#include "Planet.h"
#include "LightManager.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "Cube.h"
#include "Player.h"

class World {
public:
	World();
	void init(Camera *camera, Player *player);
	void update(GLfloat deltaTime);
	void draw();

private:
	std::vector<Planet> planets;
	Camera *camera;

	Player *player;
};
