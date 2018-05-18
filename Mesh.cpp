#include "Mesh.h"


#define POSITION_LOCATION    0
#define TEX_COORD_LOCATION   1
#define NORMAL_LOCATION      2
#define BONE_ID_LOCATION     3
#define BONE_WEIGHT_LOCATION 4


Mesh::MeshEntry::MeshEntry() {
	baseVertex = 0;
	baseIndex = 0;
	numIndices = 0;
	materialIndex = INVALID_MATERIAL;
};

void Mesh::VertexBoneData::AddBoneData(unsigned int boneID, float weight) {
	for (unsigned int i = 0; i < NUM_BONES_PER_INDEX; i++) {
		if (weights[i] == 0) {
			IDs[i] = boneID;
			weights[i] = weight;
			return;
		}
	}
}

Mesh::Mesh(std::string filename)
{
	
	diffuseDefault = new ModelTexture(Loader::LoadTexture("char/diffuse.png"));
	normalDefault = new ModelTexture(Loader::LoadTexture("char/normal.png"));
	emissiveDefault = new ModelTexture(Loader::LoadTexture("res/textureDefault/emissive.png"));
	specularDefault = new ModelTexture(Loader::LoadTexture("char/specular.png"));

	VAO = 0;
	memset(&mBuffers, 0, sizeof(unsigned int)*NUMOFVBS);
	mNumofBones = 0;
	mpScene = NULL;
	animated = 0;
	LoadMesh(filename);
}

Mesh::~Mesh()
{
	Clear();
}

bool Mesh::LoadMesh(const std::string filename)
{

	Clear();

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(NUMOFVBS, mBuffers);

	bool ret = false;
	mpScene = Loader::LoadScene(filename, aiProcess_Triangulate
		| aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);
	/*aiImportFile(filename.c_str(), aiProcess_Triangulate
	| aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);*/

	if (mpScene != NULL) {
		aiMatrix4x4 global = mpScene->mRootNode->mTransformation;
		mGlobalInverseTransform = Maths::Mat4FromAiMat4(global.Inverse());

		ret = InitFromScene(mpScene, filename);
	}
	else {
		std::cout << "Error parsing " << filename << " " << aiGetErrorString() << std::endl;
	}

	glBindVertexArray(0);
	return ret;
}

void Mesh::Render(AnimatedShader* ss)
{
	glBindVertexArray(VAO);

	for (unsigned int i = 0; i < mEntries.size(); i++) {

		const unsigned int materialIndex = mEntries[i].materialIndex;

		if (materialIndex < mTextures.size()) {
			
			//Debug4(mTextures[materialIndex]->textureID, mSpecularMaps[materialIndex]->textureID,mEmissiveMaps[materialIndex]->textureID, mNormalMaps[materialIndex]->textureID);
						
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, mTextures[materialIndex]->textureID);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, mSpecularMaps[materialIndex]->textureID);
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, mEmissiveMaps[materialIndex]->textureID);
			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, mNormalMaps[materialIndex]->textureID);
		}

		glDrawElementsBaseVertex(GL_TRIANGLES, mEntries[i].numIndices, GL_UNSIGNED_INT, (void*)(sizeof(unsigned int)*mEntries[i].baseIndex), mEntries[i].baseVertex);
	}
	
	glBindVertexArray(0);
}

bool Mesh::InitFromScene(const aiScene * pScene, const std::string filename)
{
	mEntries.resize(pScene->mNumMeshes);
	mTextures.resize(pScene->mNumMaterials);
	mNormalMaps.resize(pScene->mNumMaterials);
	mSpecularMaps.resize(pScene->mNumMaterials);
	mEmissiveMaps.resize(pScene->mNumMaterials);

	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texCoords;
	std::vector<VertexBoneData> bones;
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
	bones.resize(numVertices);
	indices.reserve(numIndices);

	if (mpScene->mNumAnimations > 0) {
		animated = 1;
	}

	for (unsigned int i = 0; i < mEntries.size(); i++) {
		const aiMesh* paiMesh = pScene->mMeshes[i];
		InitMesh(i, paiMesh, positions, normals, texCoords, bones, indices);
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

	//if (bones.size() > 0) {

	std::vector<unsigned int> auxIDs;
	std::vector<float> auxWeights;

	for (unsigned int k = 0; k < bones.size(); k++) {
		auxIDs.emplace_back(bones[k].IDs[0]);
		auxIDs.emplace_back(bones[k].IDs[1]);
		auxIDs.emplace_back(bones[k].IDs[2]);
		auxIDs.emplace_back(bones[k].IDs[3]);

		float normalize = bones[k].weights[0] + bones[k].weights[1] + bones[k].weights[2] + bones[k].weights[3];

		auxWeights.emplace_back(bones[k].weights[0] / normalize);
		auxWeights.emplace_back(bones[k].weights[1] / normalize);
		auxWeights.emplace_back(bones[k].weights[2] / normalize);
		auxWeights.emplace_back(bones[k].weights[3] / normalize);
	}
	/*
	glBindBuffer(GL_ARRAY_BUFFER, mBuffers[BONEVB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(bones[0]) * bones.size(), &bones[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(BONE_ID_LOCATION);
	glVertexAttribIPointer(BONE_ID_LOCATION, 4, GL_INT, sizeof(VertexBoneData), (const GLvoid*)0);
	glEnableVertexAttribArray(BONE_WEIGHT_LOCATION);
	glVertexAttribPointer(BONE_WEIGHT_LOCATION, 4, GL_FLOAT, GL_FALSE, sizeof(VertexBoneData), (const GLvoid*)16);*/

	glBindBuffer(GL_ARRAY_BUFFER, mBuffers[BONEVB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(auxIDs[0]) * auxIDs.size(), &auxIDs[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(BONE_ID_LOCATION);
	glVertexAttribIPointer(BONE_ID_LOCATION, 4, GL_INT, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, mBuffers[BONEWEIGHT]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(auxWeights[0]) * auxWeights.size(), &auxWeights[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(BONE_WEIGHT_LOCATION);
	glVertexAttribPointer(BONE_WEIGHT_LOCATION, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBuffers[INDEXBUFFER]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	return glGetError() == GL_NO_ERROR;
}

void Mesh::InitMesh(unsigned int index, const aiMesh * paiMesh, std::vector<glm::vec3>& positions, std::vector<glm::vec3>& normals, std::vector<glm::vec2>& texCoords, std::vector<VertexBoneData>& bones, std::vector<unsigned int>& indices)
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

	LoadBones(index, paiMesh, bones);

	for (unsigned int i = 0; i < paiMesh->mNumFaces; i++) {
		aiFace& face = paiMesh->mFaces[i];

		indices.emplace_back(face.mIndices[0]);
		indices.emplace_back(face.mIndices[1]);
		indices.emplace_back(face.mIndices[2]);
	}
}

bool Mesh::InitMaterials(const aiScene * pScene, const std::string filename)
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

	std::cout << "numMat: " << pScene->mNumMaterials << std::endl;

	for (unsigned int i = 0; i < pScene->mNumMaterials; i++) {
		const aiMaterial* pMaterial = pScene->mMaterials[i];

		mTextures[i] = NULL;
		mNormalMaps[i] = NULL;
		mEmissiveMaps[i] = NULL;
		mSpecularMaps[i] = NULL;
		if (pMaterial->GetTextureCount(aiTextureType_UNKNOWN) > 0)
			Debug("unknow");
		if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
			aiString path;

			std::cout << "diffuse " << i << std::endl;
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
		if (pMaterial->GetTextureCount(aiTextureType_SHININESS) > 0) {
			std::cout << "Here!";
		}

		if (pMaterial->GetTextureCount(aiTextureType_NORMALS) > 0) {
			aiString path;
			if (pMaterial->GetTexture(aiTextureType_NORMALS, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
				std::string fullpath = Dir + "/" + path.data;

				mNormalMaps[i] = new ModelTexture(Loader::LoadTexture(fullpath));

			}
		}

		if (pMaterial->GetTextureCount(aiTextureType_EMISSIVE) > 0) {
			aiString path;
			if (pMaterial->GetTexture(aiTextureType_EMISSIVE, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
				std::string fullpath = Dir + "/" + path.data;
				mEmissiveMaps[i] = new ModelTexture(Loader::LoadTexture(fullpath));
			}
		}

		if (pMaterial->GetTextureCount(aiTextureType_SPECULAR) > 0) {
			aiString path;
			if (pMaterial->GetTexture(aiTextureType_SPECULAR, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
				std::string fullpath = Dir + "/" + path.data;
				mSpecularMaps[i] = new ModelTexture(Loader::LoadTexture(fullpath));
			}
		}

		if (mTextures[i] == NULL) {
			mTextures[i] = diffuseDefault;
		}
		if (mNormalMaps[i] == NULL) {
			mNormalMaps[i] = normalDefault;
		}
		if (mEmissiveMaps[i] == NULL) {
			mEmissiveMaps[i] = emissiveDefault;			
		}
		if (mSpecularMaps[i] == NULL) {
			mSpecularMaps[i] = specularDefault;
		}
	}

	return ret;
}

void Mesh::LoadBones(unsigned int index, const aiMesh * pMesh, std::vector<VertexBoneData>& bones)
{
	for (unsigned int i = 0; i < pMesh->mNumBones; i++) {
		unsigned int boneIndex = 0;
		std::string boneName(pMesh->mBones[i]->mName.data);

		//std::cout << boneName << std::endl;
		if (boneMapping.find(boneName) == boneMapping.end()) {
			boneIndex = mNumofBones;
			mNumofBones++;
			BoneInfo bi;
			mBoneInfo.emplace_back(bi);
			mBoneInfo[boneIndex].boneOffset = glm::transpose(Maths::Mat4FromAiMat4(pMesh->mBones[i]->mOffsetMatrix));
			boneMapping[boneName] = boneIndex;
		}
		else {
			boneIndex = boneMapping[boneName];
		}

		for (unsigned int j = 0; j < pMesh->mBones[i]->mNumWeights; j++) {
			unsigned int vertexID = mEntries[index].baseVertex + pMesh->mBones[i]->mWeights[j].mVertexId;
			float weight = pMesh->mBones[i]->mWeights[j].mWeight;
			bones[vertexID].AddBoneData(boneIndex, weight);
		}
	}

}

unsigned int Mesh::FindPosition(float animationTime, const aiNodeAnim * pNodeAnim)
{
	for (unsigned int i = 0; i < pNodeAnim->mNumPositionKeys - 1; i++) {
		if (animationTime < (float)pNodeAnim->mPositionKeys[i + 1].mTime) {
			return i;
		}
	}
	return 0;
}

unsigned int Mesh::FindRotation(float animationTime, const aiNodeAnim * pNodeAnim)
{
	for (unsigned int i = 0; i < pNodeAnim->mNumRotationKeys - 1; i++) {
		if (animationTime < (float)pNodeAnim->mRotationKeys[i + 1].mTime) {
			return i;
		}
	}
	return 0;
}

unsigned int Mesh::FindScaling(float animationTime, const aiNodeAnim * pNodeAnim)
{
	for (unsigned int i = 0; i < pNodeAnim->mNumScalingKeys - 1; i++) {
		if (animationTime < (float)pNodeAnim->mScalingKeys[i + 1].mTime) {
			return i;
		}
	}
	return 0;
}

void Mesh::CalcInterpolatedPos(aiVector3D & out, float animationTime, const aiNodeAnim * pNodeAnim)
{
	if (pNodeAnim->mNumPositionKeys == 1) {
		out = pNodeAnim->mPositionKeys[0].mValue;
		return;
	}

	unsigned int positionIndex = FindPosition(animationTime, pNodeAnim);
	unsigned int nextPositionIndex = (positionIndex + 1);

	float DeltaTime = (float)(pNodeAnim->mPositionKeys[nextPositionIndex].mTime - pNodeAnim->mPositionKeys[positionIndex].mTime);
	float Factor = (animationTime - (float)pNodeAnim->mPositionKeys[positionIndex].mTime) / DeltaTime;

	const aiVector3D& Start = pNodeAnim->mPositionKeys[positionIndex].mValue;
	const aiVector3D& End = pNodeAnim->mPositionKeys[nextPositionIndex].mValue;
	aiVector3D Delta = End - Start;
	out = Start + Factor * Delta;
}

void Mesh::CalcInterpolatedRot(aiQuaternion & out, float animationTime, const aiNodeAnim * pNodeAnim)
{
	if (pNodeAnim->mNumRotationKeys == 1) {
		out = pNodeAnim->mRotationKeys[0].mValue;
		return;
	}

	unsigned int RotationIndex = FindRotation(animationTime, pNodeAnim);
	unsigned int NextRotationIndex = (RotationIndex + 1);

	float DeltaTime = (float)(pNodeAnim->mRotationKeys[NextRotationIndex].mTime - pNodeAnim->mRotationKeys[RotationIndex].mTime);
	float Factor = (animationTime - (float)pNodeAnim->mRotationKeys[RotationIndex].mTime) / DeltaTime;

	const aiQuaternion& StartRotationQ = pNodeAnim->mRotationKeys[RotationIndex].mValue;
	const aiQuaternion& EndRotationQ = pNodeAnim->mRotationKeys[NextRotationIndex].mValue;

	aiQuaternion helper;
	aiQuaternion::Interpolate(helper, StartRotationQ, EndRotationQ, Factor);

	out = helper.Normalize();
}

void Mesh::CalcInterpolatedScaling(aiVector3D & out, float animationTime, const aiNodeAnim * pNodeAnim)
{
	if (pNodeAnim->mNumScalingKeys == 1) {
		out = pNodeAnim->mScalingKeys[0].mValue;
		return;
	}

	unsigned int ScalingIndex = FindScaling(animationTime, pNodeAnim);
	unsigned int NextScalingIndex = (ScalingIndex + 1);

	float DeltaTime = (float)(pNodeAnim->mScalingKeys[NextScalingIndex].mTime - pNodeAnim->mScalingKeys[ScalingIndex].mTime);
	float Factor = (animationTime - (float)pNodeAnim->mScalingKeys[ScalingIndex].mTime) / DeltaTime;

	const aiVector3D& Start = pNodeAnim->mScalingKeys[ScalingIndex].mValue;
	const aiVector3D& End = pNodeAnim->mScalingKeys[NextScalingIndex].mValue;
	aiVector3D Delta = End - Start;
	Delta = (Start + (Factor*Delta));
	out = Delta;
}

void Mesh::ReadNodeHierarchy(float animationTime, const aiNode * pNode, const glm::mat4 &parentTransform)
{

	std::string nodeName(pNode->mName.data);
	if (mpScene->mNumAnimations == 0) {
		return;
	}

	const aiAnimation* pAnimation = mpScene->mAnimations[0];

	glm::mat4  NodeTransformation = (Maths::Mat4FromAiMat4(pNode->mTransformation));

	const aiNodeAnim* pNodeAnim = FindNodeAnim(pAnimation, nodeName);


	if (pNodeAnim) {
		// Interpolate scaling and generate scaling transformation matrix
		aiVector3D scaling;
		CalcInterpolatedScaling(scaling, animationTime, pNodeAnim);
		glm::mat4 scalingM;

		scalingM = glm::scale(scalingM, Maths::Vec3FromAiVec3(scaling));

		// Interpolate rotation and generate rotation transformation matrix
		aiQuaternion rotationQ;
		CalcInterpolatedRot(rotationQ, animationTime, pNodeAnim);
		glm::mat4 rotationM = glm::toMat4(Maths::QuatFromAiQuat(rotationQ));

		// Interpolate translation and generate translation transformation matrix
		aiVector3D translation;
		CalcInterpolatedPos(translation, animationTime, pNodeAnim);
		glm::mat4 translationM;

		translationM = glm::translate(translationM, Maths::Vec3FromAiVec3(translation));

		// Combine the above transformations
		NodeTransformation = translationM * rotationM * scalingM;
	}

	glm::mat4 GlobalTransformation = parentTransform * NodeTransformation;

	if (boneMapping.find(nodeName) != boneMapping.end()) {
		unsigned int boneIndex = boneMapping[nodeName];
		// WTF here!
		//!
		auto aux = mGlobalInverseTransform * GlobalTransformation * mBoneInfo[boneIndex].boneOffset;
		mBoneInfo[boneIndex].finalTransform = mGlobalInverseTransform * GlobalTransformation * mBoneInfo[boneIndex].boneOffset;
	}

	for (unsigned int i = 0; i < pNode->mNumChildren; i++) {
		ReadNodeHierarchy(animationTime, pNode->mChildren[i], GlobalTransformation);
	}
}


void Mesh::BoneTransform(float timeInSeconds, std::vector<glm::mat4>& transforms)
{
	if (mpScene->mNumAnimations == 0)
		return;

	glm::mat4 identity;

	float ticksPerSecond = (float)(mpScene->mAnimations[0]->mTicksPerSecond != 0 ? mpScene->mAnimations[0]->mTicksPerSecond : 25.f);
	float timeInTicks = timeInSeconds * ticksPerSecond;
	float animationTime = fmod(timeInTicks, (float)mpScene->mAnimations[0]->mDuration);

	std::queue<aiNode*>nodes;
	std::queue<glm::mat4>matrices;

	nodes.push(mpScene->mRootNode);
	matrices.push(identity);

	while (!nodes.empty()) {
		aiNode* pNode = nodes.front();
		nodes.pop();

		glm::mat4 parentTransform = matrices.front();
		matrices.pop();

		std::string nodeName(pNode->mName.data);
		if (mpScene->mNumAnimations == 0) {
			break;
		}

		const aiAnimation* pAnimation = mpScene->mAnimations[0];

		glm::mat4  NodeTransformation = (Maths::Mat4FromAiMat4(pNode->mTransformation));

		const aiNodeAnim* pNodeAnim = FindNodeAnim(pAnimation, nodeName);

		if (pNodeAnim) {
			// Interpolate scaling and generate scaling transformation matrix
			aiVector3D scaling;
			CalcInterpolatedScaling(scaling, animationTime, pNodeAnim);
			glm::mat4 scalingM;

			scalingM = glm::scale(scalingM, Maths::Vec3FromAiVec3(scaling));

			// Interpolate rotation and generate rotation transformation matrix
			aiQuaternion rotationQ;
			CalcInterpolatedRot(rotationQ, animationTime, pNodeAnim);
			glm::mat4 rotationM = glm::toMat4(Maths::QuatFromAiQuat(rotationQ));

			// Interpolate translation and generate translation transformation matrix
			aiVector3D translation;
			CalcInterpolatedPos(translation, animationTime, pNodeAnim);
			glm::mat4 translationM;

			translationM = glm::translate(translationM, Maths::Vec3FromAiVec3(translation));

			// Combine the above transformations
			NodeTransformation = translationM * rotationM * scalingM;
		}

		glm::mat4 GlobalTransformation = parentTransform * NodeTransformation;

		if (boneMapping.find(nodeName) != boneMapping.end()) {
			unsigned int boneIndex = boneMapping[nodeName];
			// WTF here!
			//!
			auto aux = mGlobalInverseTransform * GlobalTransformation * mBoneInfo[boneIndex].boneOffset;
			mBoneInfo[boneIndex].finalTransform = mGlobalInverseTransform * GlobalTransformation * mBoneInfo[boneIndex].boneOffset;
		}

		for (unsigned int i = 0; i < pNode->mNumChildren; i++) {
			nodes.push(pNode->mChildren[i]);
			matrices.push(GlobalTransformation);
			//ReadNodeHierarchy(animationTime, pNode->mChildren[i], GlobalTransformation);
		}
	}

	//ReadNodeHierarchy(animationTime, mpScene->mRootNode, identity);

	transforms.resize(mNumofBones);

	for (unsigned int i = 0; i < mNumofBones; i++) {
		transforms[i] = mBoneInfo[i].finalTransform;
	}
}

const aiNodeAnim * Mesh::FindNodeAnim(const aiAnimation * pAnimation, std::string name)
{
	for (unsigned int i = 0; i < pAnimation->mNumChannels; i++) {
		const aiNodeAnim* pNodeAnim = pAnimation->mChannels[i];


		if (std::string(pNodeAnim->mNodeName.data) == name) {
			return pNodeAnim;
		}
	}

	return NULL;
}

void Mesh::Clear()
{
	if (mBuffers[0] != 0) {
		glDeleteBuffers(NUMOFVBS, mBuffers);
	}
	if (VAO != 0) {
		glDeleteVertexArrays(1, &VAO);
	}
}
