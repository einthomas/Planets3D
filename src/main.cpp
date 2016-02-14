#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "World.h"
#include "ResourceManager.h"
#include "Game.h"

const GLuint WIDTH = 800, HEIGHT = 600;

GLFWwindow* window;
Camera* camera;
Game game;
GLfloat deltaTime = 0.0f, lastFrame = 0.0f;

bool initGLFW();
bool initGLEW();
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double posX, double posY);
void mouse_btn_callback(GLFWwindow* window, int button, int action, int mods);
void loadShaders();
void loadModels();
void loadMaterials();

int main() {
	if (!initGLFW()) return -1;

	glViewport(0, 0, WIDTH, HEIGHT);

	// Set OpenGL options
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_MULTISAMPLE);

	if (!initGLEW()) return -1;
	
	camera = new Camera(glm::vec3(0.0f, 0.0f, 0.0f));

	loadShaders();
	loadModels();
	loadMaterials();

	game.init(WIDTH, HEIGHT, camera);

	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window)) {
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();

		glClearColor(0.196078f, 0.6f, 0.8f, 1.0f);
		//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		game.processInput(deltaTime);
		game.update(deltaTime);
		game.draw();

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}

bool initGLFW() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	window = glfwCreateWindow(WIDTH, HEIGHT, "Planets3D", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetMouseButtonCallback(window, mouse_btn_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	return true;
}

bool initGLEW() {
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		return false;
	}

	return true;
}

void loadShaders() {
	glm::mat4 projectionPers = glm::perspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.01f, 800.0f);
	ResourceManager::loadShader("lighting", "shaders/lightingShader.vert", "shaders/lightingShader.frag");
	ResourceManager::getShader("lighting")->use();
	ResourceManager::getShader("lighting")->setMatrix4("projection", projectionPers);
	ResourceManager::getShader("lighting")->setVector2f("screenRes", glm::vec2(WIDTH, HEIGHT));

	ResourceManager::loadShader("lightingModel", "shaders/lightingShaderModel.vert", "shaders/lightingShaderModel.frag");
	ResourceManager::getShader("lightingModel")->use();
	ResourceManager::getShader("lightingModel")->setMatrix4("projection", projectionPers);
}

void loadModels() {
	ResourceManager::loadModel("planet1", "models/planet1.obj", camera);
	ResourceManager::loadModel("player", "models/player.obj", camera);
}

void loadMaterials() {
	Material whiteLight(0.0f, glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f));
	ResourceManager::materials["whiteLight"] = whiteLight;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	game.key_callback(key, scancode, action, mode);
}

void mouse_callback(GLFWwindow* window, double posX, double posY) {
	game.mouse_callback(posX, posY);
}

void mouse_btn_callback(GLFWwindow* window, int button, int action, int mods) {
	game.mouse_btn_callback(button, action, mods);
}
