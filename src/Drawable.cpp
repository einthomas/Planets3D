#include "Drawable.h"

Drawable::Drawable(Model model, Shader *shader) {
	this->model = model;
	this->shader = shader;
}
