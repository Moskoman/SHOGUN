#include <iostream>

#include <assimp/postprocess.h>

#include "StaticMesh.h"
#include "Loader.h"

#define POSITION_LOCATION    0
#define TEX_COORD_LOCATION   1
#define NORMAL_LOCATION      2
#define BONE_ID_LOCATION     3
#define BONE_WEIGHT_LOCATION 4

bool StaticMesh::InitFromScene(const aiScene * pScene, std::string filename)
{
	mEntries.resize(pScene->mNumMeshes);
	mTextures.resize(pScene->mNumMaterials);

	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texCoords;

	std::vector<unsigned int> indices;

	unsigned int numVertices = 0;
	unsigned int numIndices = 0;

	//ADJENCY SHIET GOES HERE SEE TUTORIAL 39 folder

	for (unsigned int i = 0; i < mEntries.size(); i++) {
		mEntries[i].materialIndex = mpScene->mMeshes[i]->mMaterialIndex;
		mEntries[i].numIndices = mpScene->mMeshes[i]->mNumFaces * 3;
		mEntries[i].baseVertex = numVertices;
		mEntries[i].baseIndex = numIndices;

		numVertices += mpScene->mMeshes[i]->mNumVertices;
		numIndices += mEntries[i].numIndices;
	}

	positions.reserve(numVertices);
	normals.reserve(numVertices);
	texCoords.reserve(numVertices);

	indices.reserve(numIndices);

	for (unsigned int i = 0; i < mEntries.size(); i++) {
		const aiMesh* paiMesh = pScene->mMeshes[i];
		InitMesh(i, paiMesh, positions, normals, texCoords, indices);
	}

	if (!InitMaterials(pScene, filename)) {
		return false;
	}

	glBindBuffer(GL_ARRAY_BUFFER, mBuffers[POSVB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions[0]) * positions.size(), &positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(POSITION_LOCATION);
	glVertexAttribPointer(POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, mBuffers[TEXCVB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords[0]) * texCoords.size(), &texCoords[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(TEX_COORD_LOCATION);
	glVertexAttribPointer(TEX_COORD_LOCATION, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, mBuffers[NORMVB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normals[0]) * normals.size(), &normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(NORMAL_LOCATION);
	glVertexAttribPointer(NORMAL_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBuffers[INDEXBUFFER]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	return glGetError() == GL_NO_ERROR;
}

bool StaticMesh::Initialize(std::string filename)
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(NUMOFVBS, mBuffers);

	bool ret = false;

	Loader loader = Loader();
	mpScene = loader.LoadScene(filename, aiProcess_Triangulate
		| aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);

	if (mpScene != NULL) {
		aiMatrix4x4 global = mpScene->mRootNode->mTransformation;
		ret = InitFromScene(mpScene, filename);
	}
	else {
		std::cout << "Error parsing " << filename << " " << aiGetErrorString() << std::endl;
	}

	glBindVertexArray(0);
	return ret;
}

StaticMesh::StaticMesh(std::string filename)
{
	type = STATIC;
	Initialize(filename);
}
//
//void StaticMesh::Render(ShaderProgram* sp)
//{
//	StaticShader* ss = (StaticShader*)sp;
//
//	glBindVertexArray(VAO);
//	glEnableVertexAttribArray(0);
//	glEnableVertexAttribArray(1);
//	glEnableVertexAttribArray(2);
//
//
//	for (unsigned int i = 0; i < mEntries.size(); i++) {
//
//		const unsigned int materialIndex = mEntries[i].materialIndex;
//
//		if (materialIndex < mTextures.size()) {
//			ss->loadShineVariables(mTextures[materialIndex]->shineDamper, mTextures[materialIndex]->reflectivity);
//			glActiveTexture(GL_TEXTURE0);
//			glBindTexture(GL_TEXTURE_2D, mTextures[materialIndex]->textureID);
//		}
//
//		glDrawElementsBaseVertex(GL_TRIANGLES, mEntries[i].numIndices, GL_UNSIGNED_INT, (void*)(sizeof(unsigned int)*mEntries[i].baseIndex), mEntries[i].baseVertex);
//	}
//
//	glDisableVertexAttribArray(0);
//	glDisableVertexAttribArray(1);
//	glDisableVertexAttribArray(2);
//
//	glBindVertexArray(0);
//}

void StaticMesh::Update(float dt)
{

}


void StaticMesh::InitMesh(unsigned int index, const aiMesh * paiMesh, std::vector<glm::vec3>& positions, std::vector<glm::vec3>& normals, std::vector<glm::vec2>& texCoords, std::vector<unsigned int>& indices)
{
	mEntries[index].materialIndex = paiMesh->mMaterialIndex;

	const aiVector3D zero3D(0.f, 0.f, 0.f);

	for (unsigned int i = 0; i < paiMesh->mNumVertices; i++) {
		const aiVector3D* pPos = &(paiMesh->mVertices[i]);
		const aiVector3D* pNormal = &(paiMesh->mNormals[i]);
		const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &zero3D;

		positions.emplace_back(glm::vec3(pPos->x, pPos->y, pPos->z));
		normals.emplace_back(glm::vec3(pNormal->x, pNormal->y, pNormal->z));
		texCoords.emplace_back(glm::vec2(pTexCoord->x, pTexCoord->y));
	}

	for (unsigned int i = 0; i < paiMesh->mNumFaces; i++) {
		aiFace& face = paiMesh->mFaces[i];

		indices.emplace_back(face.mIndices[0]);
		indices.emplace_back(face.mIndices[1]);
		indices.emplace_back(face.mIndices[2]);
	}
}


bool StaticMesh::InitMaterials(const aiScene * pScene, const std::string filename)
{
	std::string::size_type SlashIndex = filename.find_last_of("/");
	std::string Dir;

	if (SlashIndex == std::string::npos) {
		Dir = ".";
	}
	else if (SlashIndex == 0) {
		Dir = "/";
	}
	else {
		Dir = filename.substr(0, SlashIndex);
	}

	bool ret = true;

	for (unsigned int i = 0; i < pScene->mNumMaterials; i++) {
		const aiMaterial* pMaterial = pScene->mMaterials[i];

		mTextures[i] = NULL;

		if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
			aiString path;
			if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
				std::string fullpath = Dir + "/" + path.data;

				mTextures[i] = new ModelTexture(Loader::LoadTexture(fullpath));

				if (mTextures[i] != NULL) {
					//pMaterial->mProperties[k] pontos interessantes k = 9 shininess , 10 reflectivity, 11 refraction, 12 opacity 
					for (int k = 0; k < pMaterial->mNumProperties; k++) {
						if (pMaterial->mProperties[k]->mKey.data == "$mat.shininess") {
							std::vector<char> data(pMaterial->mProperties[k]->mDataLength);
							memcpy_s(data.data(), pMaterial->mProperties[k]->mDataLength, pMaterial->mProperties[k]->mData, pMaterial->mProperties[k]->mDataLength);
							float toFloat;
							memcpy_s(&toFloat, sizeof(float), data.data(), data.size() * sizeof(char));
							mTextures[i]->shineDamper = toFloat;
						}

						if (pMaterial->mProperties[k]->mKey.data == "$mat.reflectivity") {
							std::vector<char> data(pMaterial->mProperties[k]->mDataLength);
							memcpy_s(data.data(), pMaterial->mProperties[k]->mDataLength, pMaterial->mProperties[k]->mData, pMaterial->mProperties[k]->mDataLength);
							float toFloat;
							memcpy_s(&toFloat, sizeof(float), data.data(), data.size() * sizeof(char));
							mTextures[i]->reflectivity = toFloat;
						}
					}
				}

			}

		}

		if (mTextures[i] == NULL) {
			mTextures[i] = new ModelTexture(Loader::LoadTexture("res/d.png"));
		}
	}

	return ret;
}
