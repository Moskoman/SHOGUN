#include "SkyboxShader.h"
#include "Debug.h"
#include <glm/gtc/matrix_access.hpp>
#include "Game.h"


SkyboxShader::SkyboxShader() : ShaderProgram("shaders//skybox.vs", "shaders//skybox.fs")
{
	bindAttributes();
	ShaderProgram::LinkAndValidateProgram();
	getAllUniformLocations();
}

SkyboxShader::~SkyboxShader()
{
}

void SkyboxShader::loadProjectionMatrix(mat4 matrix)
{
	ShaderProgram::loadMatrix(location_projectionMatrix, matrix);
}

void SkyboxShader::loadViewMatrix(Camera camera)
{
	mat4 viewMatrix = Maths::createViewMatrix(camera);
	
	viewMatrix[0][3] = 0;
	viewMatrix[1][3] = 0;
	viewMatrix[2][3] = 0;

	rotation += rotation_speed * Game::GetInstance()->GetDeltaTime();
	viewMatrix = rotate(viewMatrix, radians(rotation), vec3(0, 1, 0));

	ShaderProgram::loadMatrix(location_viewMatrix, viewMatrix);
}

void SkyboxShader::bindAttributes() {
	Debug("SkyboxShaderBindAttributes");
	bindAttribute(0, "position");
}

void SkyboxShader::LoadBlend(float b) {
	ShaderProgram::loadFloat(location_blend,b);
}

void SkyboxShader::connectTextureUnits() {
	ShaderProgram::loadInt(location_cubeMap, 0);
	ShaderProgram::loadInt(location_cubeMap2, 1);
}

void SkyboxShader::getAllUniformLocations() {
	location_projectionMatrix = ShaderProgram::getUniformLocation("projectionMatrix");
	location_viewMatrix = ShaderProgram::getUniformLocation("viewMatrix");
	location_blend = ShaderProgram::getUniformLocation("blendFactor");
	location_cubeMap = ShaderProgram::getUniformLocation("cubeMap");
	location_cubeMap2 = ShaderProgram::getUniformLocation("cubeMap2");
}
