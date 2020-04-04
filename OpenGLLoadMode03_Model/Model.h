#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.h"

//#include "stb_image.h"
using std::vector;
using std::string;
using std::map;
class Model
{
public:
	Model(string path);
	~Model();
	vector<Mesh> meshes;
	string directory;
	void Draw(Shader* shader);
private:
	map<string, Texture> textures_loaded;
	void loadModel(string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
	unsigned int TextureFromFile(string path, const string& directory);
};

