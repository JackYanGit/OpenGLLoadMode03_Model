#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <string>
#include <vector>
#include "Shader.h"
using std::vector;
using std::string;
struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoord;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
};
struct Texture {
	unsigned int id;
	string type;
	string path;
};
class Mesh
{
public:
	//Íø¸ñÊý¾Ý
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;
	Mesh(float* vertices);
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
	void Draw(Shader* shader);

private:
	unsigned int VAO, VBO, EBO;
	void setupMesh();
};

