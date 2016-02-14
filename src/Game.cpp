#include "Game.h"

Game::Game() { }

void Game::init(GLuint width, GLuint height, Camera* camera) {
	this->width = width;
	this->height = height;
	this->camera = camera;

	player = new Player(ResourceManager::getModel("player"), ResourceManager::getShader("lightingModel"));
	world.init(camera, player);
}

void Game::update(GLuint deltaTime) {
	world.update(deltaTime);
}

void Game::draw() {
	world.draw();
}

void Game::processInput(GLfloat deltaTime) {
	if (keys[GLFW_KEY_W]) {
		camera->handleKeyboardInput(Movement::FORWARD, deltaTime);
	}
	if (keys[GLFW_KEY_S]) {
		camera->handleKeyboardInput(Movement::BACKWARD, deltaTime);
	}
	if (keys[GLFW_KEY_A]) {
		camera->handleKeyboardInput(Movement::LEFT, deltaTime);
	}
	if (keys[GLFW_KEY_D]) {
		camera->handleKeyboardInput(Movement::RIGHT, deltaTime);
	}
	if (keys[GLFW_KEY_SPACE]) {
		camera->handleKeyboardInput(Movement::UPWARD, deltaTime);
	}
	if (keys[GLFW_KEY_LEFT_SHIFT]) {
		camera->handleKeyboardInput(Movement::DOWNWARD, deltaTime);
	}
	if (keys[GLFW_KEY_UP]) {
		player->handleKeyboardInput(Movement::FORWARD, deltaTime);
	}
	if (keys[GLFW_KEY_LEFT]) {
		player->handleKeyboardInput(Movement::LEFT, deltaTime);
	}
	if (keys[GLFW_KEY_RIGHT]) {
		player->handleKeyboardInput(Movement::RIGHT, deltaTime);
	}
	if (keys[GLFW_KEY_DOWN]) {
		player->handleKeyboardInput(Movement::BACKWARD, deltaTime);
	}
}


// Input callbacks
void Game::key_callback(int key, int scancode, int action, int mode) {
	if (action == GLFW_PRESS)
		keys[key] = true;
	if (action == GLFW_RELEASE) {
		keys[key] = false;
	}
}

void Game::mouse_callback(double posX, double posY) {
	if (firstMouse) {
		lastX = posX;
		lastY = posY;
		firstMouse = false;
	}

	GLfloat offsetX = posX - lastX;
	GLfloat offsetY = lastY - posY;
	lastX = posX;
	lastY = posY;

	camera->handleMouseInput(offsetX, offsetY);
}

void Game::mouse_btn_callback(int button, int action, int mods) {
	if (action == GLFW_PRESS) {
	}
}
