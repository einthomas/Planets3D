#include "Model.h"

Model::Model() { }

Model::Model(GLchar* path, Camera *camera, glm::vec3 scale, glm::vec3 pos)
{
	this->camera = camera;
	this->scale = scale;

	loadModel(path);
	setPos(pos);
}

void Model::draw(Shader *shader)
{
	for (int i = 0; i < meshes.size(); i++)
		meshes[i].draw(shader);
}

void Model::loadModel(std::string path)
{
	Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		std::string s = importer.GetErrorString();

		return;
	}

	directory = path.substr(0, path.find_last_of('/'));
	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	for (GLuint i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}

	for (GLuint i = 0; i < node->mNumChildren; i++)
		processNode(node->mChildren[i], scene);
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	for (GLuint i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;

		glm::vec3 vector;
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.pos = vector;

		if (mesh->HasNormals())
		{
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.normal = vector;
		}

		if (mesh->mTextureCoords[0])		// check if the mesh contains texture coordinates
		{
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.texCoords = vec;
		}
		else
			vertex.texCoords = glm::vec2(0.0f, 0.0f);

		vertices.push_back(vertex);
	}

	for (GLuint i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (GLuint k = 0; k < face.mNumIndices; k++)
			indices.push_back(face.mIndices[k]);
	}

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		if (material->GetTextureCount(aiTextureType_DIFFUSE) == 0 && material->GetTextureCount(aiTextureType_SPECULAR) == 0) {
			aiColor3D ac(0.0f, 0.0f, 0.0f);
			material->Get(AI_MATKEY_COLOR_AMBIENT, ac);
			glm::vec3 ambientColor(ac.r, ac.g, ac.b);

			aiColor3D dc(0.0f, 0.0f, 0.0f);
			material->Get(AI_MATKEY_COLOR_DIFFUSE, dc);
			glm::vec3 diffuseColor(dc.r, dc.g, dc.b);

			aiColor3D sc(0.0f, 0.0f, 0.0f);
			material->Get(AI_MATKEY_COLOR_SPECULAR, sc);
			glm::vec3 specularColor(sc.r, sc.g, sc.b);

			return Mesh(vertices, indices, Material(0.0f, ambientColor, diffuseColor, specularColor), camera, scale);
		} else {
			std::vector<Texture> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

			std::vector<Texture> specularMaps = this->loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		}
	}

	return Mesh(vertices, indices, textures, camera, scale);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
	std::vector<Texture> textures;
	aiString s;
	GLboolean skipLoading = false;

	for (GLuint i = 0; i < mat->GetTextureCount(type); i++)
	{
		mat->GetTexture(type, i, &s);

		for (GLuint k = 0; k < loadedTextures.size(); k++)
		{
			if (loadedTextures[k].path == s)
			{
				textures.push_back(loadedTextures[k]);
				skipLoading = true;
				break;
			}
		}

		if (!skipLoading)
		{
			Texture texture;

			texture.id = ResourceManager::loadTexture(std::string(directory + '/' + s.C_Str()).c_str());
			texture.type = typeName;
			texture.path = s;

			textures.push_back(texture);
		}
	}

	return textures;
}

void Model::setPos(glm::vec3 pos)
{
	this->pos = pos;
	for (int i = 0; i < meshes.size(); i++)
		meshes[i].pos = pos;
}

glm::vec3 Model::getFirstVertexPos()
{
    glm::vec3 firstVertexPos = meshes[0].getFirstVertexPos();
 	glm::mat4 m;
	m = glm::translate(m, pos);
	glm::vec4 a = m * glm::vec4(firstVertexPos.x, firstVertexPos.y, firstVertexPos.z, 1.0f);

	return glm::vec3(a.x, a.y, a.z);
}
