#pragma once
#include <glm\glm.hpp>
#include "TexturedModel.h"
#include "Mesh.h"

using namespace glm;

class Entity
{
public:
	Mesh * mesh;
	vec3 position;
	vec3 rotation;
	float scale;

	vector<mat4>transforms;

	float time;

	//int textureIndex;

	void Translate(vec3 pos);
	void Rotate(vec3 rot);

	//float getTextureXOffset();
	//float getTextureYOffset();

	Mesh* GetMesh();
	void Update(float dt);

	vector<mat4> GetTransforms();
	Entity(Mesh* m, glm::vec3 p, glm::vec3 r, float s);
	//Entity(glm::vec3 position, glm::vec3 rotation, float scale, int textureIndex); //varias textura em um obj
	~Entity();
};

