#include "Util.h"

vector<string> Util::split(string s, char delimiter) {
	stringstream strstream(s);
	string part;
	vector<string> elems;

	while (getline(strstream, part, delimiter)) {
		elems.push_back(part);
		part = "";
	}

	return elems;
}

/*
	theta = arccos(z/r)
	phi = arctan(y/x)
*/
void Util::cartesianToSpherical(glm::vec3 cartesianCoords, GLfloat radius, GLfloat &theta, GLfloat &phi) {
	cartesianCoords = Util::degreeToRadian(cartesianCoords);
	theta = acosf(cartesianCoords.z / radius);		// Problem: acos ist nur für Werte zwischen -1 und 1 definiert
	phi = atan2f(cartesianCoords.y, cartesianCoords.x);
}

/*
	x = r * sin(theta) * cos(phi)
	y = r * sin(theta) * sin(phi)
	z = r * cos(theta)
*/
glm::vec3 Util::sphericalToCartesian(GLfloat radius, GLfloat theta, GLfloat phi) {
	glm::vec3 cartesianCoords;
	cartesianCoords.x = radius * sinf(theta) * cosf(phi);
	cartesianCoords.y = radius * sinf(theta) * sinf(phi);
	cartesianCoords.z = radius * cosf(theta);
	
	return cartesianCoords;
}

glm::vec3 Util::radianToDegree(glm::vec3 radian) {
	return radian * (GLfloat)(180.0f / M_PI);
}

glm::vec3 Util::degreeToRadian(glm::vec3 degree) {
	return degree * (GLfloat)(M_PI / 180.0f);
}
