#include "TerrainRenderer.h"
#include "MasterRenderer.h"

//
//TerrainRenderer::TerrainRenderer(TerrainShader * shader, mat4 projectionMatrix) : shader(shader)
//{
//	shader->start();
//	shader->loadProjectionMatrix(projectionMatrix);
//	shader->connectTextureUnits();
//	shader->stop();
//}
//
//void TerrainRenderer::render(vector<Terrain> terrains)
//{
//	for (uint i = 0; i < terrains.size(); i++) {
//		prepareTerrain(terrains[i]);
//		loadModelMatrix(terrains[i]);
//
//		glDrawElements(GL_TRIANGLES, terrains[i].model.vertexCount, GL_UNSIGNED_INT, 0);
//
//		unbindTexturedModel();
//	}
//
//}
//
//TerrainRenderer::~TerrainRenderer()
//{
//}
//
//
//void TerrainRenderer::prepareTerrain(Terrain terrain)
//{
//	glBindVertexArray(terrain.model.vaoID);
//	glEnableVertexAttribArray(0);
//	glEnableVertexAttribArray(1);
//	glEnableVertexAttribArray(2);
//	ModelTexture texture = terrain.texture;
//	shader->loadShineVariables(texture.shineDamper, texture.reflectivity);
//	bindTextures(terrain);
//}
//
//void TerrainRenderer::bindTextures(Terrain terrain)
//{
//	TerrainTexturePack ttp = terrain.ttp;
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, ttp.backgroundTexture);
//	glActiveTexture(GL_TEXTURE1);
//	glBindTexture(GL_TEXTURE_2D, ttp.r);
//	glActiveTexture(GL_TEXTURE2);
//	glBindTexture(GL_TEXTURE_2D, ttp.g);
//	glActiveTexture(GL_TEXTURE3);
//	glBindTexture(GL_TEXTURE_2D, ttp.b);
//	glActiveTexture(GL_TEXTURE4);
//	glBindTexture(GL_TEXTURE_2D, terrain.texture.textureID);
//}
//
//void TerrainRenderer::unbindTexturedModel()
//{
//	glDisableVertexAttribArray(0);
//	glDisableVertexAttribArray(1);
//	glDisableVertexAttribArray(2);
//	glBindVertexArray(0);
//}
//
//void TerrainRenderer::loadModelMatrix(Terrain go)
//{
//	glm::mat4 transformationMatrix = Maths::createTransformationMatrix(vec3(go.x, -5, go.z), vec3(0,0,0), 1);
//	shader->loadTransformationMatrix(transformationMatrix);
//}