#include "Loader.h"
#include "Debug.h"
#define STB_IMAGE_IMPLEMENTATION   
#include <stb_image.h>
#include "Game.h"


vector<GLuint> Loader::vaos;
vector<GLuint> Loader::vbos;
vector<GLuint> Loader::textureList;
//unordered_map<string, ModelTexture*> textureMap;
unordered_map<string, unsigned int> Loader::textureMap;
unordered_map<string, const aiScene *> Loader::scenesMap;
unordered_map<string, Mesh*> Loader::modelsMap;


const aiScene * Loader::LoadScene(std::string filename, unsigned int flags)
{
	const aiScene* aux;
	if (scenesMap.find(filename) == scenesMap.end()) {
		aux = aiImportFile(filename.c_str(), flags);

		scenesMap[filename] = aux;
	}
	else {
		aux = scenesMap[filename];
	}

	return aux;
}

Mesh * Loader::LoadModel(std::string filename)
{
	if (modelsMap.find(filename) == modelsMap.end()) {
		Mesh* mesh = new Mesh(filename);
		modelsMap[filename] = mesh;
	}

	return modelsMap[filename];
}


//
//RawModel Loader::loadToVAO(vector<vec3> positions, vector<vec2> textureCoords, vector<vec3> normals, vector<int> indices)
//{
//	GLuint vaoID = createVAO();
//	storeDataInAttributeList(0, positions);
//
//	Debug4("TextureCoords",textureCoords.size(), "normals", normals.size());
//	storeDataInAttributeList(1, textureCoords);
//	storeDataInAttributeList(2, normals);
//	bindIndicesBuffer(indices);
//	unbindVAO();
//	return RawModel(vaoID, indices.size());
//}

RawModel Loader::loadToVAO(vector<vec2> positions)
{
	GLuint vaoID = createVAO();
	storeDataInAttributeList(0, positions);
	unbindVAO();
	return RawModel(vaoID, positions.size());
}

RawModel Loader::loadToVAO(vector<vec3> positions)
{
	GLuint vaoID = createVAO();
	storeDataInAttributeList(0, positions);
	unbindVAO();
	return RawModel(vaoID, positions.size());
}

void Loader::Clear()
{
	while (!vbos.empty()) {
		glDeleteBuffers(1, &vbos.back());
		vbos.pop_back();
	}

	while (!vaos.empty()) {
		glDeleteVertexArrays(1, &vaos.back());
		vaos.pop_back();
	}

	Debug("Clearing models\n.");
	for (auto i = modelsMap.begin(); i != modelsMap.end(); i++) {
		delete i->second;
	}

	modelsMap.clear();

	Debug("Clearing scenes.\n");
	for (auto i = scenesMap.begin(); i != scenesMap.end(); i++) {
		aiReleaseImport(i->second);
	}

	scenesMap.clear();

	Debug("Clearing textures.\n");
	while (!textureList.empty()) {
		glDeleteTextures(1, &textureList.back());
		textureList.pop_back();
	}
}



GLuint Loader::LoadTexture(std::string filename)
{
	/*if (textureMap.find(filename) != textureMap.end()) {
	return &textureMap[filename];
	}*/

	if (textureMap.find(filename) == textureMap.end()) {
		ilutRenderer(ILUT_OPENGL);
		int textureID = ilutGLLoadImage((char*)filename.c_str());

		textureMap[filename] = textureID;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.4F);


		textureList.emplace_back(textureID);
	}

	Debug("Loading texture: " << filename);
	


	return textureMap[filename];

	/*
	textureMap[filename] = ModelTexture(textureID);
	Debug(textureMap[filename].textureID);*/
}

GLuint Loader::LoadTexture2(string file)
{

	if (textureMap.find(file) != textureMap.end()) {
		return textureMap[file];
	}

	GLuint textureID = NULL;
	ILuint ImgId;

	ilGenImages(1, &ImgId);
	ilBindImage(ImgId);

	ilLoadImage(file.data());

	void * data = ilGetData();
	if (!data) {
		ilBindImage(0);
		ilDeleteImages(1, &ImgId);
		return 0;
	}

	int const width = ilGetInteger(IL_IMAGE_WIDTH);
	int const height = ilGetInteger(IL_IMAGE_HEIGHT);
	int const type = ilGetInteger(IL_IMAGE_TYPE); // matches OpenGL
	int const format = ilGetInteger(IL_IMAGE_FORMAT); // matches OpenGL

	Debug4(width, height, type, format);

	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, type, data);
	glGenerateMipmap(GL_TEXTURE_2D);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.4F);

	//textureList.emplace_back(textureID);

	textureMap[file] = textureID;

	return textureID;
}

GLuint Loader::LoadCubeMap(vector<string> filename)
{
	if (textureMap.find(filename[0]) != textureMap.end()) {
		return textureMap[filename[0]];
	}

	GLuint textureID = NULL;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	unsigned char *data;

	for (int i = 0; i < 6; i++) {
		

		data = stbi_load(filename[i].c_str(), &width, &height, &nrChannels, 0);
		glTexImage2D(
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
			0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
		);
				

	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	textureMap[filename[0]] = textureID;
	Debug(textureID);
	return textureID;
}
//
GLuint Loader::createVAO()
{
	GLuint vao;
	glGenVertexArrays(1, &vao);
	vaos.emplace_back(vao);
	glBindVertexArray(vao);
	return vao;
}
//
template <typename T>
void Loader::storeDataInAttributeList(int attributeNumber, vector<T> data)
{
	GLuint VBO;
	vbos.emplace_back(VBO);

	int coordinateSize = 3;

	if (is_same<T, vec4>::value) { coordinateSize = 4; }
	else if (is_same<T, vec2>::value) { coordinateSize = 2; }

	// Gera o Vertex Buffer Object
	glGenBuffers(1, &VBO);
	// Bind our first VBO as being the active buffer and storing vertex attributes (coordinates)
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Copy the vertex data from vertices to our buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(T) * data.size(), data.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(attributeNumber, coordinateSize, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::unbindVAO()
{
	glBindVertexArray(0);
}

//void Loader::bindIndicesBuffer(vector<int> indices)
//{
//	GLuint vboID;
//	glGenBuffers(1, &vboID);
//	vbos.emplace_back(vboID);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), indices.data(), GL_STATIC_DRAW);
//}
