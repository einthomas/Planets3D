#pragma once

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm.hpp>
#include <vector>
#include <string>
#include <sstream>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

class Util {
public:
	static vector<string> split(string s, char delimiter);
	static void cartesianToSpherical(glm::vec3 cartesianCoords, GLfloat radius, GLfloat &theta, GLfloat &phi);
	static glm::vec3 sphericalToCartesian(GLfloat radius, GLfloat theta, GLfloat phi);
	static glm::vec3 radianToDegree(glm::vec3 radian);
	static glm::vec3 degreeToRadian(glm::vec3 degree);
};
