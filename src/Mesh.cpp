#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures, Camera *camera, glm::vec3 scale) {
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
	this->camera = camera;
	this->scale = scale;

	hasTexture = true;
	setupMesh();
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, Material material, Camera *camera, glm::vec3 scale) {
	this->vertices = vertices;
	this->indices = indices;
	this->material = material;
	this->camera = camera;
	this->scale = scale;

	hasTexture = false;
	setupMesh();
}

void Mesh::draw(Shader *shader)
{
	shader->use();

	glm::mat4 model = glm::mat4();
	model = glm::translate(model, pos);
	model = glm::scale(model, scale);
	shader->setMatrix4("model", model);
	shader->setMatrix4("view", camera->getViewMatrix());
	shader->setVector3f("viewPos", camera->pos);

	GLuint directionalID = 0;
	GLuint pointID = 0;
	GLuint spotID = 0;

	for (GLuint i = 0; i < LightManager::lights.size(); i++) {
		std::string varName;

		if (LightManager::lights[i]->type == LightType::DIRECTIONAL) {
			varName = "dirLight";
			shader->setVector3f((varName + ".dir").c_str(), LightManager::lights[directionalID++]->dir);
		} 
		else if (LightManager::lights[i]->type == LightType::POINT) {
			varName = "pointLights[" + std::to_string(pointID++) + "]";
			shader->setVector3f((varName + ".pos").c_str(), LightManager::lights[i]->pos);
			shader->setFloat((varName + ".constant").c_str(), LightManager::lights[i]->constant);
			shader->setFloat((varName + ".linear").c_str(), LightManager::lights[i]->linear);
			shader->setFloat((varName + ".quadratic").c_str(), LightManager::lights[i]->quadratic);
		}
		else if (LightManager::lights[i]->type == LightType::SPOT || LightManager::lights[i]->type == LightType::FLASH) {
			varName = "spotLights[" + std::to_string(spotID++) + "]";
			shader->setVector3f((varName + ".pos").c_str(), LightManager::lights[i]->pos);
			shader->setFloat((varName + ".constant").c_str(), LightManager::lights[i]->constant);
			shader->setFloat((varName + ".linear").c_str(), LightManager::lights[i]->linear);
			shader->setFloat((varName + ".quadratic").c_str(), LightManager::lights[i]->quadratic);

			shader->setVector3f((varName + ".dir").c_str(), LightManager::lights[i]->dir);
			shader->setFloat((varName + ".innerCutOff").c_str(), LightManager::lights[i]->innerCutOff);
			shader->setFloat((varName + ".outerCutOff").c_str(), LightManager::lights[i]->outerCutOff);
		}

		shader->setVector3f((varName + ".ambient").c_str(), LightManager::lights[i]->material.ambient);
		shader->setVector3f((varName + ".diffuse").c_str(), LightManager::lights[i]->material.diffuse);
		shader->setVector3f((varName + ".specular").c_str(), LightManager::lights[i]->material.specular);
	}

	shader->setInteger("hasTexture", hasTexture);

	if (hasTexture) {
		GLuint diffuseNr = 0;
		GLuint specularNr = 0;
		for (GLuint i = 0; i < textures.size(); i++) {
			std::string name = textures[i].type;
			if (name == "material.textureDiffuse")
				name += std::to_string(diffuseNr++);
			else if (name == "material.textureSpecular")
				name += std::to_string(specularNr++);

			//shader->setFloat(name.c_str(), i);
			shader->setInteger(name.c_str(), i);
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
		}

		shader->setFloat("material.shininess", 16.0f);
	} else {
		shader->setFloat("material.shininess", 16.0f);
		shader->setVector3f("material.diffuseColor", material.diffuse);
		shader->setVector3f("material.specularColor", material.specular);
	}

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	if (hasTexture) {
		for (GLuint i = 0; i < textures.size(); i++) {
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}

void Mesh::setupMesh() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() *  sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	// positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	// normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

	if (hasTexture) {
		// texture coords
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoords));
	}

	glBindVertexArray(0);
}

glm::vec3 Mesh::getFirstVertexPos() {
	return vertices[0].pos;
}
