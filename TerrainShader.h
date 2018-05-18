#pragma once
#include "ShaderProgram.h"
#include "Camera.h"
#include "Light.h"
#include "Maths.h"
class TerrainShader :
	public ShaderProgram
{
private:
	GLint location_transformationMatrix;
	GLint location_projectionMatrix;
	GLint location_viewMatrix;
	GLint location_lightPosition;
	GLint location_lightColor;
	GLint location_shineDamper;
	GLint location_reflectivity;
	GLint location_skyColor;
	GLint location_rTexture;
	GLint location_gTexture;
	GLint location_bTexture;
	GLint location_backgroundTexture;
	GLint location_blendMap;
public:
	void connectTextureUnits();
	void bindAttributes();
	void getAllUniformLocations();
	void loadSkyColor(float r, float g, float b);
	void loadLight(DirectionalLight light);
	void loadShineVariables(float damper, float reflectivity);
	void loadTransformationMatrix(mat4 matrix);
	void loadProjectionMatrix(mat4 matrix);
	void loadViewMatrix(Camera camera);
	TerrainShader();
	~TerrainShader();
};

