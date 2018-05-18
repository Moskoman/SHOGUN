#include "ParticleShader.h"
#include "Debug.h"
ParticleShader::ParticleShader() : ShaderProgram("shaders//particle.vs", "shaders//particle.fs")
{
	bindAttributes();
	ShaderProgram::LinkAndValidateProgram();
	getAllUniformLocations();
}

ParticleShader::~ParticleShader()
{
}

void ParticleShader::loadProjectionMatrix(mat4 matrix)
{
	ShaderProgram::loadMatrix(location_projectionMatrix, matrix);
}

void ParticleShader::loadModelViewMatrix(mat4 matrix)
{
	
	ShaderProgram::loadMatrix(location_modelViewMatrix, matrix);
}

void ParticleShader::bindAttributes() {
	Debug("ParticleShaderBindAttributes");
	bindAttribute(0, "position");
}

void ParticleShader::loadTextureCoordInfo(vec2 offset1, vec2 offset2, float numRows, float blend)
{
	ShaderProgram::load2DVector(location_texOffset1, offset1);
	ShaderProgram::load2DVector(location_texOffset2, offset2);
	ShaderProgram::load2DVector(location_texCoordInfo, vec2(numRows, blend));
}

void ParticleShader::getAllUniformLocations() {
	location_projectionMatrix = ShaderProgram::getUniformLocation("projectionMatrix");
	location_modelViewMatrix = ShaderProgram::getUniformLocation("modelViewMatrix");
	location_texCoordInfo = ShaderProgram::getUniformLocation("texCoordInfo");
	location_texOffset1 = ShaderProgram::getUniformLocation("texOffset1");
	location_texOffset2 = ShaderProgram::getUniformLocation("texOffset2");

}
