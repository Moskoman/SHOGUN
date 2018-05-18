#include "TerrainShader.h"
#include "Debug.h"


TerrainShader::TerrainShader() :ShaderProgram("terrainvertexshader.txt", "terrainfragmentshader.txt")
{
	bindAttributes();
	ShaderProgram::LinkAndValidateProgram();
	
	getAllUniformLocations();
}

TerrainShader::~TerrainShader()
{
	
}

void TerrainShader::connectTextureUnits()
{
	ShaderProgram::loadInt(location_backgroundTexture, 0);
	ShaderProgram::loadInt(location_rTexture, 1);
	ShaderProgram::loadInt(location_gTexture, 2);
	ShaderProgram::loadInt(location_bTexture, 3);
	ShaderProgram::loadInt(location_blendMap, 4);

}

void TerrainShader::bindAttributes() {
	Debug("TerrainShaderBindAttributes");
	bindAttribute(0, "position");
	bindAttribute(1, "textureCoords");
	bindAttribute(2, "normal");

}

void TerrainShader::getAllUniformLocations() {
	location_transformationMatrix = ShaderProgram::getUniformLocation("transformationMatrix");
	location_projectionMatrix = ShaderProgram::getUniformLocation("projectionMatrix");
	location_viewMatrix = ShaderProgram::getUniformLocation("viewMatrix");
	location_lightPosition = ShaderProgram::getUniformLocation("lightPosition");
	location_lightColor = ShaderProgram::getUniformLocation("lightColor");
	location_shineDamper = ShaderProgram::getUniformLocation("shineDamper");
	location_reflectivity = ShaderProgram::getUniformLocation("reflectivity");
	location_skyColor = ShaderProgram::getUniformLocation("skyColor");
	location_rTexture = ShaderProgram::getUniformLocation("rSampler");
	location_gTexture = ShaderProgram::getUniformLocation("gSampler");
	location_bTexture = ShaderProgram::getUniformLocation("bSampler");
	location_backgroundTexture = ShaderProgram::getUniformLocation("textureSampler");
	location_blendMap = ShaderProgram::getUniformLocation("blendMap");
}


void TerrainShader::loadSkyColor(float r, float g, float b) {
	ShaderProgram::loadVector(location_skyColor, vec3(r, g, b));
}

void TerrainShader::loadLight(DirectionalLight light) {
	ShaderProgram::loadVector(location_lightColor, light.ambient);
	ShaderProgram::loadVector(location_lightPosition, light.direction);
}

void TerrainShader::loadShineVariables(float damper, float reflectivity) {
	ShaderProgram::loadFloat(location_shineDamper, damper);
	ShaderProgram::loadFloat(location_reflectivity, reflectivity);
}

void TerrainShader::loadTransformationMatrix(mat4 matrix)
{
	ShaderProgram::loadMatrix(location_transformationMatrix, matrix);
}

void TerrainShader::loadProjectionMatrix(mat4 matrix)
{
	ShaderProgram::loadMatrix(location_projectionMatrix, matrix);
}

void TerrainShader::loadViewMatrix(Camera camera)
{
	mat4 viewMatrix = Maths::createViewMatrix(camera);
	ShaderProgram::loadMatrix(location_viewMatrix, viewMatrix);
}

