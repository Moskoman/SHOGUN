#pragma once

#include <string>
#include <unordered_map>
#include <assimp/scene.h>
#include <glm/glm.hpp>
#include "ModelTexture.h"
#include "AnimatedShader.h"
#include <iostream>
#include <queue>
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <gl/glew.h>
#include <IL/ilut.h>
#include "Maths.h"
#include "Loader.h"
#include "ModelTexture.h"

class Mesh {
public:
	Mesh(std::string filename);
	~Mesh();
	
	ModelTexture * diffuseDefault;
	ModelTexture * specularDefault;
	ModelTexture * normalDefault;
	ModelTexture * emissiveDefault;

	bool LoadMesh(const std::string filename);

	void Render(AnimatedShader* ss);
	
	int animated;

	unsigned int NumBones() {
		return mNumofBones;
	}
	void BoneTransform(float timeInSeconds, std::vector<glm::mat4>& transforms);
	std::vector<glm::mat4> transforms;
	//std::vector<glm::mat4> GetBoneFinalTransforms();

	

private:
	struct BoneInfo {
		glm::mat4 boneOffset;
		glm::mat4 finalTransform;

		BoneInfo() {
			boneOffset = glm::mat4(0);
			finalTransform = glm::mat4(0);
		}
	};

#define NUM_BONES_PER_INDEX 4 
	struct VertexBoneData {
		unsigned int IDs[NUM_BONES_PER_INDEX];
		float weights[NUM_BONES_PER_INDEX];

		VertexBoneData() {
			memset(&IDs, 0, NUM_BONES_PER_INDEX * sizeof(unsigned int));
			memset(&weights, 0, NUM_BONES_PER_INDEX * sizeof(float));
		}

		void AddBoneData(unsigned int boneID, float weight);
	};

	bool InitFromScene(const aiScene* pScene, const std::string filename);
	void InitMesh(unsigned int index, const aiMesh* paiMesh,
		std::vector<glm::vec3>& positions, std::vector<glm::vec3>& normals,
		std::vector<glm::vec2>& texCoords, std::vector<VertexBoneData>& bones,
		std::vector<unsigned int>& indices);
	bool InitMaterials(const aiScene* pScene, const std::string filename);
	void LoadBones(unsigned int index, const aiMesh* pMesh, std::vector<VertexBoneData>& bones);

	unsigned int FindPosition(float animationTime, const aiNodeAnim* pNodeAnim);
	unsigned int FindRotation(float animationTime, const aiNodeAnim* pNodeAnim);
	unsigned int FindScaling(float animationTime, const aiNodeAnim* pNodeAnim);

	void CalcInterpolatedPos(aiVector3D &out, float animationTime, const aiNodeAnim* pNodeAnim);
	void CalcInterpolatedRot(aiQuaternion &out, float animationTime, const aiNodeAnim* pNodeAnim);
	void CalcInterpolatedScaling(aiVector3D &out, float animationTime, const aiNodeAnim* pNodeAnim);
	void ReadNodeHierarchy(float animationTime, const aiNode* pNode, const glm::mat4 &parentTransform);

	const aiNodeAnim* FindNodeAnim(const aiAnimation* pAnimation, std::string name);

	void Clear();

#define INVALID_MATERIAL 0xFFFFFFFF //-1 

	struct MeshEntry {
		MeshEntry();

		unsigned int baseVertex; //Vertex Buffer
		unsigned int baseIndex; //Index Buffer

		unsigned int numIndices;
		unsigned int materialIndex;
	};


	enum VB_TYPES {
		INDEXBUFFER,
		POSVB,
		NORMVB,
		TEXCVB,
		BONEVB,
		BONEWEIGHT,
		ANIMATED,
		NUMOFVBS
	};

	unsigned int mBuffers[NUMOFVBS];


	std::vector<MeshEntry> mEntries;

	vector<ModelTexture*> mTextures;
	vector<ModelTexture*> mNormalMaps;
	vector<ModelTexture*> mSpecularMaps;
	vector<ModelTexture*> mEmissiveMaps;

	unsigned int mNumofBones;
	glm::mat4 mGlobalInverseTransform;

	std::unordered_map<std::string, unsigned int> boneMapping;
	std::vector<BoneInfo> mBoneInfo;

	const aiScene* mpScene;
public:

	unsigned int VAO;

};
