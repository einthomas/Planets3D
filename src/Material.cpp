#include "Material.h"

Material::Material() { }

Material::Material(GLfloat shininess, GLuint diffuseMap, GLuint specularMap) {
	this->shininess = shininess;
	this->diffuseMap = diffuseMap;
	this->specularMap = specularMap;
}

Material::Material(GLfloat shininess, GLuint diffuseMap, GLuint specularMap, Image *heightMap) {
	this->shininess = shininess;
	this->diffuseMap = diffuseMap;
	this->specularMap = specularMap;
	this->heightMap = heightMap;
}

Material::Material(GLfloat shininess, GLuint ambientMap, GLuint diffuseMap, GLuint specularMap) {
	this->shininess = shininess;
	this->ambientMap = ambientMap;
	this->diffuseMap = diffuseMap;
	this->specularMap = specularMap;
}

Material::Material(GLfloat shininess, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) {
	this->shininess = shininess;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
}
