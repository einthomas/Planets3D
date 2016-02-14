#include "Planet.h"

Planet::Planet(glm::vec3 pos, Model model, Shader *shader) 
	: Drawable(model, shader) {
	iron = 1000;
	silver = 1000;
	water = 1000;

	this->model.setPos(pos);
	radius = calcRadius();
	diameter = radius * 2;
}

void Planet::update(GLfloat deltaTime) {
}

void Planet::draw() {
	model.draw(shader);
}

GLuint Planet::calcRadius() {
	return abs((model.getFirstVertexPos() - model.pos).length());
}
