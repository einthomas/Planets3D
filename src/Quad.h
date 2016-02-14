#pragma once

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <SOIL.h>
#include "imageloader.h"

#include "Shape.h"
#include "Camera.h"
#include "Shader.h"
#include "LightManager.h"

class Quad : public Shape
{
public:
	Quad(Camera *camera, Shader *shader, glm::vec3 pos, glm::vec3 scale, Material material, GLfloat rotation);
	Quad(Shader *shader, glm::vec3 pos, glm::vec3 scale, GLuint texture, GLfloat rotation, GLboolean staticPos);
	void update(GLfloat dt);
	void draw();
	GLuint getVAO();
	GLuint getVAOWithHeightmap();

private:
	std::vector<std::vector<glm::vec3>> positions;
	glm::vec3 vertCount;

	void readHeightmap();
	void applySmoothingFilter(const float c);
	std::vector<std::vector<glm::vec3>> computeNormals();
};
