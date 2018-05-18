#pragma once

#include "RawModel.h"
#include "Mesh.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <assimp\scene.h>

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <IL\il.h>
#include <IL\ilut.h>
#include <IL\ilu.h>

#include "ModelTexture.h"

using namespace std;
using namespace glm;

class Mesh;

class Loader
{
public:
	static const aiScene* LoadScene(string filename, unsigned int flags);
	static Mesh* LoadModel(string filename);
	static void Clear();
	static GLuint LoadTexture(string file);
	static GLuint LoadTexture2(string file);

	static GLuint LoadCubeMap(vector<string> filename);

	static RawModel loadToVAO(vector<vec2> positions);
	static RawModel loadToVAO(vector<vec3> positions);
private:
	static vector<GLuint> vaos;
	static vector<GLuint> vbos;
	static vector<GLuint> textureList;
	//unordered_map<string, ModelTexture*> textureMap;
	static unordered_map<string, unsigned int> textureMap;
	static unordered_map<string, const aiScene *> scenesMap;
	static unordered_map<string, Mesh*> modelsMap;

	/*RawModel loadToVAO(vector<vec3> positions, vector<vec2> textureCoord, vector<vec3> normals, vector<int> indices);
	*/ // GUI
	static GLuint createVAO();

	template <typename T>
	static void storeDataInAttributeList(int attributeNumber, vector<T> data);
	static void unbindVAO();
	//void bindIndicesBuffer(vector<int> indices);
};

