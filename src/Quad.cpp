#include "Quad.h"

Quad::Quad(Camera *camera, Shader *shader, glm::vec3 pos, glm::vec3 scale, Material material, GLfloat rotation)
	: Shape(0, camera, shader, pos, scale, material, rotation)
{
	if (material.heightMap != nullptr)
	{
		vertCount.x = material.heightMap->width;
		vertCount.y = material.heightMap->height;

		VAO = getVAOWithHeightmap();
	}
	else
		VAO = getVAO();
}

Quad::Quad(Shader *shader, glm::vec3 pos, glm::vec3 scale, GLuint texture, GLfloat rotation, GLboolean staticPos)
	: Shape(0, shader, pos, scale, texture, rotation, staticPos)
{
	VAO = getVAO();
}

void Quad::update(GLfloat dt)
{
}

void Quad::draw()
{
	Shape::draw();

	glBindVertexArray(VAO);
	if (material.heightMap != nullptr)
		glDrawElements(GL_TRIANGLES, ((vertCount.x - 1) * 6) * (vertCount.y - 1), GL_UNSIGNED_INT, 0);
	else
	{
		if (staticPos)
			shader->setTexture2D("texture", GL_TEXTURE0, texture, 0);
			//glBindTexture(GL_TEXTURE_2D, texture);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
	glBindVertexArray(0);
}

void Quad::readHeightmap()
{
	positions.resize((GLuint)vertCount.y);
	for (GLuint y = 0; y < (GLuint)vertCount.y; y++)
	{
		positions[y].resize((GLuint)vertCount.x);
		for (GLuint x = 0; x < (GLuint)vertCount.x; x++)
		{
			unsigned char color = (unsigned char)material.heightMap->pixels[3 * (y * (GLuint)vertCount.x + x)];
			float height = (color / 255.0f) * -0.1f;
			positions[y][x] = glm::vec3(0.0f, 0.0f, height);
		}
	}
}

GLuint Quad::getVAO()
{
	GLfloat vertices[] = {
		 // Pos					// TexCoords	// Normals
		 1.0f,  1.0f, 0.0f,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f,		// Top Right
	 	 1.0f, -1.0f, 0.0f,		1.0f, 0.0f,		0.0f, 1.0f, 0.0f,		// Bottom Right
		-1.0f, -1.0f, 0.0f,		0.0f, 0.0f,		0.0f, 1.0f, 0.0f,		// Bottom Left
		-1.0f,  1.0f, 0.0f,		0.0f, 1.0f,		0.0f, 1.0f, 0.0f		// Top Left 
	};
	
	GLuint indices[] = {
		0, 1, 3,	// First Triangle
		1, 2, 3		// Second Triangle
	};
	
	GLuint VBO, VAO, EBO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);
	
	glBindVertexArray(VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	// Pos
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	
	// TexCoords
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	
	// Normals
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	
	glBindVertexArray(0);
	
	return VAO;
}

GLuint Quad::getVAOWithHeightmap()
{
	std::vector<GLfloat> vertices;
	std::vector<std::vector<glm::vec3>> normals;
	std::vector<GLuint> indices;

	readHeightmap();

	glm::vec2 texCoordStep(1.0f / vertCount.x, 1.0f / vertCount.y);
	GLfloat stepSize = 2.0f / (vertCount.x - 1);
	for (GLuint y = 0; y < (GLuint)vertCount.y; y++)
	{
		for (GLuint x = 0; x < (GLuint)vertCount.x; x++)
		{
			positions[y][x].x = (stepSize * x);
			positions[y][x].y = (stepSize * y);
		}
	}

	//applySmoothingFilter(0.8f);
	normals = computeNormals();

	for (GLuint y = 0; y < (GLuint)vertCount.y; y++)
	{
		for (GLuint x = 0; x < (GLuint)vertCount.x; x++)
		{
			vertices.push_back(positions[y][x].x);
			vertices.push_back(positions[y][x].y);
			vertices.push_back(positions[y][x].z);

			vertices.push_back(1.0f - (texCoordStep.x * x));
			vertices.push_back(1.0f - (texCoordStep.y * y));

			vertices.push_back(normals[y][x].x);
			vertices.push_back(normals[y][x].y);
			vertices.push_back(normals[y][x].z);

			if (y < (GLuint)vertCount.y - 1 && x < (GLuint)vertCount.x - 1)
			{
				indices.push_back((vertCount.y * y) + x);
				indices.push_back((vertCount.y * y) + x + 1);
				indices.push_back((vertCount.y * y) + x + vertCount.y);

				indices.push_back((vertCount.y * y) + x + 1);
				indices.push_back((vertCount.y * y) + x + vertCount.y);
				indices.push_back((vertCount.y * y) + x + vertCount.y + 1);
			}
		}
	}

	GLuint VBO, VAO, EBO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices.front(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLfloat), &indices.front(), GL_STATIC_DRAW);

	// Pos
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// TexCoords
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	//Normals
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	return VAO;
}

void Quad::applySmoothingFilter(const float c)
{
	for (int y = 1; y < (GLuint)vertCount.y - 1; y++)
		for (int x = 0; x < (GLuint)vertCount.x - 1; x++)
			positions[y][x].z = positions[y - 1][x].z * (1 - c) + positions[y][x].z * c;

	for (int y = 0; y < (GLuint)vertCount.y - 1; y++)
		for (int x = 0; x < (GLuint)vertCount.x - 1; x++)
			positions[y][x].z = positions[y + 1][x].z * (1 - c) + positions[y][x].z * c;

	for (int y = 0; y < (GLuint)vertCount.y - 1; y++)
		for (int x = 1; x < (GLuint)vertCount.x - 1; x++)
			positions[y][x].z = positions[y][x - 1].z * (1 - c) + positions[y][x].z * c;

	for (int y = 0; y < (GLuint)vertCount.y - 1; y++)
		for (int x = 0; x < (GLuint)vertCount.x - 1; x++)
			positions[y][x].z = positions[y][x + 1].z * (1 - c) + positions[y][x].z * c;
}

std::vector<std::vector<glm::vec3>> Quad::computeNormals()
{
	std::vector<std::vector<glm::vec3>> normals;

	normals.resize((GLuint)vertCount.y);
	for (GLuint y = 0; y < vertCount.y; y++)
	{
		normals[y].resize((GLuint)vertCount.x);
		for (GLuint x = 0; x < vertCount.x; x++)
		{
			glm::vec3 v1, v2, v3, v4;
			v1 = positions[y][x];
			v2 = positions[y][x];
			v3 = positions[y][x];
			v4 = positions[y][x];

			if ((GLint)y - 1 >= 0)
				v1 = -positions[y][x] + positions[y - 1][x];
			if (y + 1 < vertCount.y)
				v2 = -positions[y][x] + positions[y + 1][x];
			if ((GLint)x - 1 >= 0)
				v3 = -positions[y][x] + positions[y][x - 1];
			if (x + 1 < vertCount.x)
				v4 = -positions[y][x] + positions[y][x + 1];

			glm::vec3 n1, n2, n3, n4;
			n1 = glm::normalize(glm::cross(v4, v1));
			n2 = glm::normalize(glm::cross(v2, v4));
			n3 = glm::normalize(glm::cross(v3, v2));
			n4 = glm::normalize(glm::cross(v1, v3));

			glm::vec3 normal = n1 + n2 + n3 + n4;
			normals[y][x] = glm::normalize(normal);
		}
	}

	return normals;
}
