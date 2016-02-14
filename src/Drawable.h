#pragma once

#include <SFML\Graphics.hpp>

#include "Model.h"
#include "Shader.h"

class Drawable {
public:
	Model model;

	Drawable(Model model, Shader *shader);
	virtual void update(GLfloat deltaTime) = 0;
	virtual void draw() = 0;

protected:
	Shader *shader;
};
