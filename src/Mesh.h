#pragma once

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>

#include "Shader.h"
#include "Camera.h"
#include "LightManager.h"
#include "Material.h"

struct Vertex
{
	glm::vec3 pos;
	glm::vec3 normal;
	glm::vec2 texCoords;
};

struct Texture
{
	GLuint id;
	std::string type;
	aiString path;
};

class Mesh
{
public:
	glm::vec3 pos;
	glm::vec3 scale;

	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures, Camera *camera, glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f));
	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, Material material, Camera *camera, glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f));
	void draw(Shader *shader);
	glm::vec3 getFirstVertexPos();

private:
	Camera *camera;
	GLuint VBO, VAO, EBO;
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;
	Material material;
	bool hasTexture;

	void setupMesh();
};
