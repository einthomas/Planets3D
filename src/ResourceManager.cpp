#include "ResourceManager.h"

std::map<const GLchar*, Shader> ResourceManager::shaders;
std::map<const GLchar*, GLuint> ResourceManager::textures;
std::map<const GLchar*, Material> ResourceManager::materials;
std::map<const GLchar*, Model*> ResourceManager::models;

Shader ResourceManager::loadShader(const GLchar* name, const GLchar* vertexSourcePath, const GLchar* fragmentSourcePath) {
	std::string vShaderSource = readFile(vertexSourcePath);
	std::string fShaderSource = readFile(fragmentSourcePath);
	const GLchar* v = vShaderSource.c_str();
	const GLchar* f = fShaderSource.c_str();
	Shader shader(v, f);
	shaders[name] = shader;

	return shader;
}

Shader *ResourceManager::getShader(const GLchar* name) {
	if (shaders.find(name) != shaders.end()) {
		return &shaders[name];
	}
}

GLuint ResourceManager::loadTexture(const GLchar* path) {
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGB);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	return texture;
}

GLuint ResourceManager::loadTexture(const GLchar* name, const GLchar* path) {
	textures[name] = loadTexture(path);
	return textures[name];
}

GLuint ResourceManager::getTexture(const GLchar* name) {
	if (textures.find(name) != textures.end()) {
		return textures[name];
	}
}

std::string ResourceManager::readFile(const GLchar* fileName) {
	std::string ret;

	std::ifstream file(fileName);
	file.seekg(0, std::ios::end);
	ret.reserve(file.tellg());
	file.seekg(0, std::ios::beg);
	ret.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	file.close();

	return ret;
}

Model ResourceManager::loadModel(const GLchar* name, GLchar* path, Camera *camera, glm::vec3 scale) {
	models[name] = new Model(path, camera, scale);
	//return Model(models[name]);		// return a (deep) copy of the loaded model
	return *models[name];
}

Model ResourceManager::getModel(const GLchar* name) {
	if (models.find(name) != models.end()) {
		//return Model(models[name]);		// return a (deep) copy of the model
		return *models[name];
	}
}
