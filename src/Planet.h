#pragma once

#include "Drawable.h"

class Planet : public Drawable {
public:
	GLuint radius, diameter;

	Planet(glm::vec3 pos, Model model, Shader *shader);
	void update(GLfloat deltaTime);
	void draw();

private:
	GLuint iron, silver, water;

	GLuint calcRadius();
};
