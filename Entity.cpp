#include "Entity.h"
#include "Debug.h"

void Entity::Translate(glm::vec3 pos)
{
	position += pos;
}

void Entity::Rotate(glm::vec3 rot)
{
	rotation += rot;
}

//float Entity::getTextureXOffset()
//{
//	int column = textureIndex % model.texture.rows;
//	return (float)column/(float)model.texture.rows;
//}
//
//float Entity::getTextureYOffset()
//{
//	int rows = textureIndex / model.texture.rows;
//	return (float)rows / (float)model.texture.rows;
//}

Entity::Entity(Mesh * m, glm::vec3 p, glm::vec3 r, float s) : mesh(m), position(p), rotation(r), scale(s), time(0)
{
}

Mesh* Entity::GetMesh()
{
	return mesh;
}

void Entity::Update(float dt)
{
	time += dt;
	mesh->BoneTransform(time, transforms);
}

std::vector<glm::mat4> Entity::GetTransforms()
{
	return transforms;
}
/*
Entity::Entity(glm::vec3 position, glm::vec3 rotation, float scale, int textureIndex) : position(position), rotation(rotation), scale(scale), textureIndex(textureIndex)
{
	Debug4("GameObject Position", position.x, position.y, position.z);
	Debug4("GameObject Rotation", rotation.x, rotation.y, rotation.z);
	Debug2("GameObject Scale", scale);

	Debug4("GameObject Model", model.rawModel.vaoID, model.rawModel.vertexCount, model.texture.textureID);
}*/

Entity::~Entity()
{
}
