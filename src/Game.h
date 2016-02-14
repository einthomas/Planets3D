#pragma once

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "Camera.h"
#include "World.h"
#include "Movement.h"

#define 	GLFW_MOUSE_BUTTON_LAST		GLFW_MOUSE_BUTTON_8
#define 	GLFW_MOUSE_BUTTON_LEFT		GLFW_MOUSE_BUTTON_1
#define 	GLFW_MOUSE_BUTTON_RIGHT		GLFW_MOUSE_BUTTON_2
#define 	GLFW_MOUSE_BUTTON_MIDDLE	GLFW_MOUSE_BUTTON_3

class Game {
public:
	GLboolean keys[1024];

	Game();
	void init(GLuint width, GLuint height, Camera* camera);
	void update(GLuint deltaTime);
	void draw();
	void processInput(GLfloat deltaTime);
	void key_callback(int key, int scancode, int action, int mode);
	void mouse_callback(double posX, double posY);
	void mouse_btn_callback(int button, int action, int mods);
	
private:
	GLuint width, height;
	Camera *camera;
	Player *player;

	GLfloat lastX = width / 2, lastY = height / 2;		// mouse pos
	bool firstMouse = true;

	World world;
};
