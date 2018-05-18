#pragma once
#include "ShaderProgram.h"
#include <glm/glm.hpp>
#include "Maths.h"

using namespace glm;

class SkyboxShader : public ShaderProgram
{

public:
	GLint location_projectionMatrix;
	GLint location_viewMatrix;
	GLint location_blend;
	GLint location_cubeMap;
	GLint location_cubeMap2;
	float rotation = 0;
	float rotation_speed = 1;

	void loadProjectionMatrix(mat4 matrix);
	void loadViewMatrix(Camera camera);
	void bindAttributes();
	void LoadBlend(float b);
	void connectTextureUnits();
	void getAllUniformLocations();
	SkyboxShader();
	~SkyboxShader();
};

