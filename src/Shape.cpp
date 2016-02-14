#include "Shape.h"

Shape::Shape(GLuint VAO, Camera *camera, Shader *shader, glm::vec3 pos, glm::vec3 scale, Material material, GLfloat rotation)
{
	this->VAO = VAO;
	this->camera = camera;
	this->shader = shader;
	this->pos = pos;
	this->scale = scale;
	this->material = material;
	this->rotation = rotation;
}

Shape::Shape(GLuint VAO, Shader *shader, glm::vec3 pos, glm::vec3 scale, GLuint texture, GLfloat rotation, GLboolean staticPos)
{
	this->VAO = VAO;
	this->shader = shader;
	this->pos = pos;
	this->scale = scale;
	this->texture = texture;
	this->rotation = rotation;
	this->staticPos = staticPos;
}

void Shape::draw()
{
	shader->use();

	glm::mat4 model = glm::mat4();
	model = glm::translate(model, pos);
	model = glm::scale(model, scale);

	if (staticPos)
	{
		shader->setMatrix4("model", model);
		shader->setTexture2D("texture", GL_TEXTURE0, texture, 0);
	}
	else
	{
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(1.0f, 0.0f, 0.0f));
		shader->setMatrix4("model", model);
		shader->setMatrix4("view", camera->getViewMatrix());

		shader->setVector3f("viewPos", camera->pos);

		shader->setFloat("material.shininess", material.shininess);
		shader->setTexture2D("material.diffuse", GL_TEXTURE0, material.diffuseMap, 0);
		shader->setTexture2D("material.specular", GL_TEXTURE1, material.specularMap, 1);

		GLuint directionalID = 0;
		GLuint pointID = 0;
		GLuint spotID = 0;

		for (GLuint i = 0; i < LightManager::lights.size(); i++)
		{
			std::string varName;

			if (LightManager::lights[i]->type == LightType::DIRECTIONAL)
			{
				varName = "dirLight";
				shader->setVector3f((varName + ".dir").c_str(), LightManager::lights[directionalID++]->dir);
			}
			else if (LightManager::lights[i]->type == LightType::POINT)
			{
				varName = "pointLights[" + std::to_string(pointID++) + "]";
				shader->setVector3f((varName + ".pos").c_str(), LightManager::lights[i]->pos);
				shader->setFloat((varName + ".constant").c_str(), LightManager::lights[i]->constant);
				shader->setFloat((varName + ".linear").c_str(), LightManager::lights[i]->linear);
				shader->setFloat((varName + ".quadratic").c_str(), LightManager::lights[i]->quadratic);
			}
			else if (LightManager::lights[i]->type == LightType::SPOT || LightManager::lights[i]->type == LightType::FLASH)
			{
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
	}
}
