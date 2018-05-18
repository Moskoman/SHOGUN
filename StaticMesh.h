#pragma once

#include <string>

#include <assimp/scene.h>
#include <glm/glm.hpp>

#include "IMesh.h"

class StaticMesh : public IMesh {
	enum VB_TYPES {
		INDEXBUFFER,
		POSVB,
		NORMVB,
		TEXCVB,
		NUMOFVBS
	};

	bool InitFromScene(const aiScene* pScene, std::string filename);
	void InitMesh(unsigned int index, const aiMesh * paiMesh, std::vector<glm::vec3>& positions, std::vector<glm::vec3>& normals, std::vector<glm::vec2>& texCoords, std::vector<unsigned int>& indices);
	bool InitMaterials(const aiScene* pScene, const std::string filename);

	unsigned int mBuffers[NUMOFVBS];

	const aiScene* mpScene;

protected:
	bool Initialize(std::string filename);
public:
	StaticMesh(std::string filename);
	//void Render(ShaderProgram* sp);
	void Update(float dt);
};
