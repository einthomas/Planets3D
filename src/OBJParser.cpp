#include "OBJParser.h"

OBJParser::OBJParser() {
}

void OBJParser::parse(string path) {
	string line;
	ifstream file(path);

	if (file.is_open()) {
		vector<glm::vec3> vertices;
		vector<glm::vec3> normals;
		vector<glm::vec2> texCoords;

		vector<glm::vec3> outVertices;
		vector<glm::vec3> outNormals;
		vector<glm::vec2> outTexCoords;

		while (getline(file, line)) {
			vector<string> splitLine = Util::split(line, ' ');

			if (splitLine[0] == "mtllib") {
				parseMTL(splitLine[1]);
			}

			if (splitLine.size() >= 4) {
				if (splitLine[0] == "v") {
					vertices.push_back(glm::vec3(stof(splitLine[1]), stof(splitLine[2]), stof(splitLine[3])));
				} else if (splitLine[0] == "vt") {
					texCoords.push_back(glm::vec2(stof(splitLine[1]), stof(splitLine[2])));
				} else if (splitLine[0] == "vn") {
					normals.push_back(glm::vec3(stof(splitLine[1]), stof(splitLine[2]), stof(splitLine[3])));
				} else if (splitLine[0] == "f") {
					for (int i = 1; i < splitLine.size(); i++) {
						vector<string> indices = Util::split(splitLine[i], '/');
						outVertices.push_back(vertices[stoi(indices[0]) - 1]);
						outNormals.push_back(normals[stoi(indices[1]) - 1]);
						outTexCoords.push_back(texCoords[stoi(indices[2]) - 1]);
					}
				}
			}
		}
	} else {
		cout << "ERROR: Unable to open file " + path << endl;
	}

	file.close();
}

void OBJParser::parseMTL(string path) {
	string line;
	ifstream file(path);

	if (file.is_open()) {
		string materialName = "";
		Material material;

		while (getline(file, line)) {
			vector<string> splitLine = Util::split(line, ' ');
			if (splitLine.size() > 0) {
				if (splitLine[0] == "newmtl" && splitLine.size() == 2) {
					if (materialName != "") {
						materials[materialName] = material;
					}
					materialName = splitLine[1];
				}
				
				if (splitLine.size() == 4) {
					if (splitLine[0] == "Ka") {
						material.ambient = glm::vec3(stof(splitLine[1]), stof(splitLine[2]), stof(splitLine[3]));
					} else if (splitLine[0] == "Kd") {
						material.diffuse = glm::vec3(stof(splitLine[1]), stof(splitLine[2]), stof(splitLine[3]));
					} else if (splitLine[0] == "Ks") {
						material.specular = glm::vec3(stof(splitLine[1]), stof(splitLine[2]), stof(splitLine[3]));
					}
				}
			}
		}

		if (materialName != "") {
			materials[materialName] = material;
		}
	} else {
		cout << "ERROR: Unable to open file " + path << endl;
	}

	file.close();
}
