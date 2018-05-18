#include "Terrain.h"
#include "Debug.h"
#include "TexturedModel.h"
//
//Terrain::Terrain(int gridX, int gridZ, Loader loader, string texFile, TerrainTexturePack ttp) : ttp(ttp){
//	Debug2(SIZE, VERTEX_COUNT);
//	texture = loader.LoadTexture(texFile);
//	Debug(texture.textureID);
//	x = gridX * SIZE;
//	z = gridZ * SIZE;
//
//	Debug3("GRIDSIZE",x, z);
//	model = GenerateTerrain(loader);
//	Debug(model.vaoID);
//}
//
//
//RawModel Terrain::GenerateTerrain(Loader loader)
//{
//	int count = VERTEX_COUNT * VERTEX_COUNT;
//	vector<glm::vec3> vertices;
//	vector<glm::vec3> normals;
//	vector<glm::vec2> textureCoord;
//	vector<int> indices;
//
//	for (int i = 0; i < VERTEX_COUNT; i++) {
//		for (int j = 0; j < VERTEX_COUNT; j++) {
//			vertices.emplace_back(glm::vec3((float)j / ((float)VERTEX_COUNT - 1) * SIZE, 0, (float)i / ((float)VERTEX_COUNT - 1) * SIZE));
//			normals.emplace_back(0, 1, 0);
//			textureCoord.emplace_back(glm::vec2((float)j / ((float)VERTEX_COUNT - 1), (float)i / ((float)VERTEX_COUNT - 1)));
//		}
//	}
//	
//	for (int gz = 0; gz<VERTEX_COUNT - 1; gz++) {
//		for (int gx = 0; gx<VERTEX_COUNT - 1; gx++) {
//			int topLeft = (gz*VERTEX_COUNT) + gx;
//			int topRight = topLeft + 1;
//			int bottomLeft = ((gz + 1)*VERTEX_COUNT) + gx;
//			int bottomRight = bottomLeft + 1;
//			indices.emplace_back(topLeft);
//			indices.emplace_back(bottomLeft);
//			indices.emplace_back(topRight);
//			indices.emplace_back(topRight);
//			indices.emplace_back(bottomLeft);
//			indices.emplace_back(bottomRight);
//		}
//	}
//		
//	return loader.loadToVAO(vertices, textureCoord, normals, indices);
//}
//
//Terrain::~Terrain()
//{
//}
