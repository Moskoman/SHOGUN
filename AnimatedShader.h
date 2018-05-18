#pragma once
#include "ShaderProgram.h"
#include "Camera.h"
#include "Light.h"
#include "Maths.h"
#include <vector>

using namespace std;
class AnimatedShader :
	public ShaderProgram
{
private:
	GLint location_transformationMatrix;
	GLint location_projectionMatrix;
	GLint location_viewMatrix;

	GLint location_diffuseMap, location_specularMap, location_emissionMap, location_shineness;
	GLint location_normalMap;
	GLint location_viewPos;

	GLint location_dirLightDirection;
	GLint location_dirLightAmbient;
	GLint location_dirLightDiffuse;
	GLint location_dirLightSpecular;

	GLint location_spotLightPosition;
	GLint location_spotLightDirection;
	GLint location_spotLightCutoff;
	GLint location_spotLightOuterCutoff;
	GLint location_spotLightConstant;
	GLint location_spotLightLinear;
	GLint location_spotLightQuadratic;
	GLint location_spotLightAmbient;
	GLint location_spotLightDiffuse;
	GLint location_spotLightSpecular;

	GLint location_pointLightPosition[4];

	GLint location_pointLightConstant[4];
	GLint location_pointLightLinear[4];
	GLint location_pointLightQuadratic[4];

	GLint location_pointLightAmbient[4];
	GLint location_pointLightDiffuse[4];
	GLint location_pointLightSpecular[4];

	int lgBones[100];
	int lAnimated;

public:
	void bindAttributes();
	void getAllUniformLocations();
	void connectMaps();
	void SetSpotLightProperties(vec3 pos, vec3 dir, vec3 ambient, vec3 diffuse, vec3 specular, int lightDistance, float cutOff, float outer);
	void SetDirectionalLightProperties(vec3 dir, vec3 ambient, vec3 diffuse, vec3 specular);
	void SetPointLightProperties(int i, vec3 pos, vec3 ambient, vec3 diffuse, vec3 specular, int lightDistance);
	vec3 lightConstants(int dist);
	void materialProperties(float shininess);
	void loadViewPos(vec3 cameraPos);
	void loadTransformationMatrix(mat4 matrix);
	void loadProjectionMatrix(mat4 matrix);
	void loadViewMatrix(Camera camera);

	void LoadBoneMatrices(std::vector<glm::mat4> matrices);

	void LoadBoolAnimated(int value);
		
	AnimatedShader();
	~AnimatedShader();
};


//#pragma once
//#include "ShaderProgram.h"
//#include "Camera.h"
//#include "Light.h"
//#include "Maths.h"
//#include <glm/glm.hpp>
//#include <string>
//#include <vector>
//
//using namespace glm;
//
//class AnimatedShader : public ShaderProgram {
//	int lTransMatrix;
//	int lProjMatrix;
//	int lViewMatrix;
//	int lLightPosition;
//	int lLightColor;
//	int lShineDamper;
//	int lReflectivity;
//	int lgBones[100];
//	int lAnimated;
//	int m_WVPLocation;
//	int m_WorldMatrixLocation;
//	int m_lightPosLocation;
//	int lViewPos;
//
//public:
//	void LoadTransformationMatrix(glm::mat4 matrix);
//	void LoadProjectionMatrix(glm::mat4 matrix);
//	void LoadBoneMatrices(std::vector<glm::mat4> matrices);
//	void LoadViewMatrix(Camera cam);
//	void LoadLight(DirectionalLight light);
//	void LoadShineVars(float damper, float shine);
//	void LoadViewPos(vec3 pos);
//	void LoadBoolAnimated(int value);
//	AnimatedShader();
//protected:
//	void bindAttributes();
//	void getAllUniformLocations();
//};