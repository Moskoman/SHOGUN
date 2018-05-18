#include "OBJLoader.h"
#include <glm\glm.hpp>
#include "Debug.h"
#include <assimp\Importer.hpp>
//
//RawModel OBJLoader::loadObjModel(string fileName, Loader loader)
//{
//	vector<vec3> positions;
//	vector<int> indices;
//	vector<vec3> normals;
//	vector<vec2> texture;
//	Assimp::Importer importer;
//	
//	const aiScene* scene = importer.ReadFile(fileName.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);
//	
//	if (!scene) {
//		exit(-1);
//	}
//
//	Debug2("Numero de Meshs", scene->mNumMeshes);
//
//	for (std::uint32_t meshId = 0u; meshId < 1; meshId++) {
//		aiMesh * mesh = scene->mMeshes[meshId];
//		//aiMaterial * material = scene->mMaterials[mesh->mMaterialIndex];
//		//aiColor4D specularColor;
//		//aiColor4D diffuseColor;
//		//aiColor4D ambientColor;
//
//		//aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &specularColor);
//		//aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diffuseColor);
//		//aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &ambientColor);
//
//		Debug2("numVert", mesh->mNumVertices);
//		for (uint32_t vertID = 0u; vertID < mesh->mNumVertices; vertID++) {
//			aiVector3D vert = mesh->mVertices[vertID];
//			aiVector3D normal = mesh->mNormals[vertID];
//
//			if (mesh->mTextureCoords[0] != NULL) {
//				aiVector3D tex;
//				tex = mesh->mTextureCoords[0][vertID];
//				texture.emplace_back(vec2(tex.x, tex.y));
//			}
//
//			normals.emplace_back(vec3(normal.x, normal.y, normal.z));
//			positions.emplace_back(vec3(vert.x, vert.y, vert.z));
//				
//			//texture.emplace_back(vec2(mesh->mTextureCoords[vertID][0].x, mesh->mTextureCoords[vertID][0].y));
//			//Debug2(mesh->mTextureCoords[0][vertID].x, mesh->mTextureCoords[0][vertID].y);
//
//		}
//
//		for (uint32_t faceID = 0u; faceID < mesh->mNumFaces; faceID++) {
//
//			assert(mesh->mFaces[faceID].mNumIndices == 3u);
//
//			indices.emplace_back(mesh->mFaces[faceID].mIndices[0u]);
//			indices.emplace_back(mesh->mFaces[faceID].mIndices[1u]);
//			indices.emplace_back(mesh->mFaces[faceID].mIndices[2u]);
//		}
//
//
//	}
//
//	RawModel model = loader.loadToVAO(positions, texture, normals, indices);
//	
//	return model;
//}
//
//OBJLoader::OBJLoader()
//{
//}
//
//
//OBJLoader::~OBJLoader()
//{
//}
