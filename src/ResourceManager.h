#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <map>

#include <GL\glew.h>
#include <SOIL.h>
#include "imageloader.h"

#include "Shader.h"
#include "Material.h"
#include "Model.h"
#include "Camera.h"

class Model;

class ResourceManager
{
public:
	static std::map<const GLchar*, Shader> shaders;
	static std::map<const GLchar*, GLuint> textures;
	static std::map<const GLchar*, Material> materials;
	static std::map<const GLchar*, Model*> models;

	static Shader loadShader(const GLchar* name, const GLchar* vertexSourcePath, const GLchar* fragmentSourcePath);
	static Shader *getShader(const GLchar* name);
	static GLuint loadTexture(const GLchar* name, const GLchar* path);
	static GLuint loadTexture(const GLchar* path);
	static GLuint getTexture(const GLchar* name);
	static Model loadModel(const GLchar* name, GLchar* path, Camera *camera, glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f));
	static Model getModel(const GLchar* name);

private:
	static std::string readFile(const GLchar* fileName);
};
