#include "World.h"

World::World() { }

void World::init(Camera *camera, Player *player) {
	this->camera = camera;
	this->player = player;

	//LightManager::lights.push_back(new DirectionalLight(glm::vec3(1.2f, 1.0f, 4.0f), ResourceManager::materials["whiteLight"]));
	//LightManager::lights.push_back(new PointLight(glm::vec3(1.2f, 1.0f, 4.0f), ResourceManager::materials["whiteLight"], 0.2f, 0.09f, 0.032f));

	LightManager::lights.push_back(new DirectionalLight(glm::vec3(-10.0, -10.0, -10.0), ResourceManager::materials["whiteLight"]));
	LightManager::lights.push_back(new PointLight(glm::vec3(-9.0f, -9.0f, -10.0f), ResourceManager::materials["whiteLight"], 1.0f, 0.09f, 0.032f));

	planets.push_back(Planet(glm::vec3(-10.0f), ResourceManager::getModel("planet1"), ResourceManager::getShader("lightingModel")));
	c = new Cube(camera, ResourceManager::getShader("lighting"), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.0f, 2.0f, 2.0f), ResourceManager::materials["whiteLight"], 0.0f);

	player->currentPlanet = &planets[0];
	player->setPos(player->currentPlanet->model.getFirstVertexPos());
}

void World::update(GLfloat deltaTime) {
	for (GLuint i = 0; i < planets.size(); i++) {
		planets[i].update(deltaTime);
	}

	player->update(deltaTime);
}

void World::draw() {
	for (GLuint i = 0; i < planets.size(); i++) {
		planets[i].draw();
	}

	player->draw();
}
