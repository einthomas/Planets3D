#pragma once

#include "Drawable.h"
#include "Planet.h"
#include "Util.h"
#include "Movement.h"

class Player : public Drawable {
public:
	Planet *currentPlanet;

	Player(Model model, Shader *shader);
	void update(GLfloat deltaTime);
	void draw();
	void handleKeyboardInput(Movement movement, GLfloat deltaTime);
	void setPos(glm::vec3 pos);

private:
	GLfloat theta, phi;
	GLfloat movementSpeed;
};
