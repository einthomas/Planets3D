#include "Camera.h"

Camera::Camera()
{
	front = glm::vec3(0.0f, 0.0f, -1.0f);
	worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
}

Camera::Camera(glm::vec3 pos)
{
	this->pos = pos;

	front = glm::vec3(0.0f, 0.0f, -1.0f);
	worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(pos, pos + front, up);
}

void Camera::handleKeyboardInput(Movement movement, GLfloat deltaTime)
{
	GLfloat camSpeed = SPEED * deltaTime;
	if (movement == Movement::FORWARD)
		pos += camSpeed * front;
	if (movement == Movement::BACKWARD)
		pos -= camSpeed * front;
	if (movement == Movement::LEFT)
		pos -= glm::normalize(glm::cross(front, up)) * camSpeed;
	if (movement == Movement::RIGHT)
		pos += glm::normalize(glm::cross(front, up)) * camSpeed;
	if (movement == Movement::UPWARD)
		pos += camSpeed * up;
	if (movement == Movement::DOWNWARD)
		pos -= camSpeed * up;
}

void Camera::handleMouseInput(GLfloat offsetX, GLfloat offsetY)
{
	GLfloat sensitivity = 0.05;
	offsetX *= sensitivity;
	offsetY *= sensitivity;

	yaw += offsetX;
	pitch += offsetY;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	this->front = glm::normalize(front);
}
