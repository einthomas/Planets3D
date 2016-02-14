#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

#include "Util.h"
#include "Material.h"

using namespace std;

class OBJParser {
	struct Vertex {
		glm::vec3 pos;
		glm::vec3 normal;
		glm::vec2 texCoords;
	};
public:
	OBJParser();
	void parse(string path);

private:
	map<string, Material> materials;

	void parseMTL(string path);
};
