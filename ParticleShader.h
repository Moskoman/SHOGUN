#pragma once
#include "ShaderProgram.h"
#include "Camera.h"
#include <glm/glm.hpp>

using namespace glm;

class ParticleShader : public ShaderProgram
{
public:

	GLuint location_projectionMatrix;
	GLuint location_modelViewMatrix;
	GLuint location_texOffset1;
	GLuint location_texOffset2;
	GLuint location_texCoordInfo;
	
	ParticleShader();
	~ParticleShader();
	void loadProjectionMatrix(mat4 matrix);
	void loadModelViewMatrix(mat4 matrix);
	void bindAttributes();

	void loadTextureCoordInfo(vec2 offset1,vec2 offset2, float numRows, float blend);
	void getAllUniformLocations();
};

