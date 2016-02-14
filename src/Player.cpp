#include "Player.h"

Player::Player(Model model, Shader *shader)
	: Drawable (model, shader) {
	movementSpeed = 1.5f;
}

void Player::update(GLfloat deltaTime) {
}

void Player::draw() {
	model.draw(shader);
}

void Player::handleKeyboardInput(Movement movement, GLfloat deltaTime) {
	switch (movement) {
		case FORWARD:
			theta += movementSpeed * deltaTime;
			break;

		case BACKWARD:
			theta -= movementSpeed * deltaTime;
			break;

		case LEFT:
			phi -= movementSpeed * deltaTime;
			break;

		case RIGHT:
			phi += movementSpeed * deltaTime;
			break;
	}

	glm::vec3 newCoords = Util::sphericalToCartesian(currentPlanet->radius, theta, phi);
	glm::mat4 m;
	m = glm::translate(m, currentPlanet->model.pos);
	glm::vec4 absolutePos = m * glm::vec4(newCoords.x, newCoords.y, newCoords.z, 1.0f);
	newCoords = glm::vec3(absolutePos.x, absolutePos.y, absolutePos.z);

	model.setPos(newCoords);
}

void Player::setPos(glm::vec3 pos) {
	model.setPos(pos);		// pos ... absolute position

	// Convert the absolute position (pos) to relative position (relative to the planet)
	glm::mat4 m;
	m = glm::translate(m, -currentPlanet->model.pos);
	glm::vec4 relativePos = m * glm::vec4(pos.x, pos.y, pos.z, 1.0f);
	Util::cartesianToSpherical(glm::vec3(relativePos.x, relativePos.y, relativePos.z), currentPlanet->radius, theta, phi);
}
