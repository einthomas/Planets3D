#include "Cube.h"

Cube::Cube(Camera *camera, Shader *shader, glm::vec3 pos, glm::vec3 scale, Material material, GLfloat rotation)
	: Shape(getVAO(), camera, shader, pos, scale, material, rotation)
{
}

void Cube::update(GLfloat dt)
{
}

void Cube::draw()
{
	Shape::draw();

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

GLuint Cube::getVAO()
{
	GLfloat vertices[] = {
		// Positions			 // Texture Coords   // Normals			
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,			0.0f,  0.0f, -1.0f,	
		 0.5f, -0.5f, -0.5f,	1.0f, 0.0f,			0.0f,  0.0f, -1.0f,	
		 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,			0.0f,  0.0f, -1.0f,	
		 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,			0.0f,  0.0f, -1.0f,	
		-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,			0.0f,  0.0f, -1.0f,	
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,			0.0f,  0.0f, -1.0f,	

		-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,			0.0f,  0.0f, 1.0f,	
		 0.5f, -0.5f,  0.5f,	1.0f, 0.0f,			0.0f,  0.0f, 1.0f,	
		 0.5f,  0.5f,  0.5f,	1.0f, 1.0f,			0.0f,  0.0f, 1.0f,	
		 0.5f,  0.5f,  0.5f,	1.0f, 1.0f,			0.0f,  0.0f, 1.0f,	
		-0.5f,  0.5f,  0.5f,	0.0f, 1.0f,			0.0f,  0.0f, 1.0f,	
		-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,			0.0f,  0.0f, 1.0f,	

		-0.5f,  0.5f,  0.5f, -	1.0f, 0.0f,			-1.0f,  0.0f,  0.0f,	
		-0.5f,  0.5f, -0.5f, -	1.0f, 1.0f,			-1.0f,  0.0f,  0.0f,	
		-0.5f, -0.5f, -0.5f, -	0.0f, 1.0f,			-1.0f,  0.0f,  0.0f,	
		-0.5f, -0.5f, -0.5f, -	0.0f, 1.0f,			-1.0f,  0.0f,  0.0f,	
		-0.5f, -0.5f,  0.5f, -	0.0f, 0.0f,			-1.0f,  0.0f,  0.0f,	
		-0.5f,  0.5f,  0.5f, -	1.0f, 0.0f,			-1.0f,  0.0f,  0.0f,	

		 0.5f,  0.5f,  0.5f,	1.0f, 0.0f,			1.0f,  0.0f,  0.0f,	
		 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,			1.0f,  0.0f,  0.0f,	
		 0.5f, -0.5f, -0.5f,	0.0f, 1.0f,			1.0f,  0.0f,  0.0f,	
		 0.5f, -0.5f, -0.5f,	0.0f, 1.0f,			1.0f,  0.0f,  0.0f,	
		 0.5f, -0.5f,  0.5f,	0.0f, 0.0f,			1.0f,  0.0f,  0.0f,	
		 0.5f,  0.5f,  0.5f,	1.0f, 0.0f,			1.0f,  0.0f,  0.0f,	

		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,			0.0f, -1.0f,  0.0f,	
		 0.5f, -0.5f, -0.5f,	1.0f, 1.0f,			0.0f, -1.0f,  0.0f,	
		 0.5f, -0.5f,  0.5f,	1.0f, 0.0f,			0.0f, -1.0f,  0.0f,	
		 0.5f, -0.5f,  0.5f,	1.0f, 0.0f,			0.0f, -1.0f,  0.0f,	
		-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,			0.0f, -1.0f,  0.0f,	
		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,			0.0f, -1.0f,  0.0f,	

		-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,			0.0f,  1.0f,  0.0f,	
		 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,			0.0f,  1.0f,  0.0f,	
		 0.5f,  0.5f,  0.5f,	1.0f, 0.0f,			0.0f,  1.0f,  0.0f,	
		 0.5f,  0.5f,  0.5f,	1.0f, 0.0f,			0.0f,  1.0f,  0.0f,	
		-0.5f,  0.5f,  0.5f,	0.0f, 0.0f,			0.0f,  1.0f,  0.0f,	
		-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,			0.0f,  1.0f,  0.0f
	};
	GLuint VBO;
	glGenBuffers(1, &VBO);

	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Positions
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
