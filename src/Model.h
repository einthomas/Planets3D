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

#include <string>
#include <iostream>
#include <vector>

#include "ResourceManager.h"
#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"

using namespace Assimp;

class ResourceManager;

class Model
{
public:
	glm::vec3 pos;
	glm::vec3 scale;

	Model();
	Model(GLchar* path, Camera *camera, glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3 pos = glm::vec3(1.0f, 1.0f, 1.0f));
	void draw(Shader *shader);
	void setPos(glm::vec3 pos);
	glm::vec3 getFirstVertexPos();

private:
	Camera *camera;
	std::vector<Mesh> meshes;
	std::vector<Texture> loadedTextures;
	std::string directory;

	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};
