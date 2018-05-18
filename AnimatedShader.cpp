#include "AnimatedShader.h"
#include "Debug.h"


AnimatedShader::AnimatedShader() :ShaderProgram("shaders//animated.vs", "shaders//animated.fs")
{
	bindAttributes();
	ShaderProgram::LinkAndValidateProgram();
	getAllUniformLocations();
}

AnimatedShader::~AnimatedShader()
{
}

void AnimatedShader::bindAttributes() {
	Debug("AnimatedShaderBindAttributes");
	bindAttribute(0, "aPos");
	bindAttribute(1, "aTexCoords");
	bindAttribute(2, "aNormal");
	bindAttribute(3, "BoneIDs");
	bindAttribute(4, "pesos");

}

void AnimatedShader::getAllUniformLocations() {
	location_transformationMatrix = ShaderProgram::getUniformLocation("model");
	location_projectionMatrix = ShaderProgram::getUniformLocation("projection");
	location_viewMatrix = ShaderProgram::getUniformLocation("view");

	location_shineness = ShaderProgram::getUniformLocation("material.shininess");
	location_emissionMap = ShaderProgram::getUniformLocation("material.emission");
	location_diffuseMap = ShaderProgram::getUniformLocation("material.diffuse");
	location_specularMap = ShaderProgram::getUniformLocation("material.specular");

	location_normalMap = ShaderProgram::getUniformLocation("normalMap");
	location_viewPos = ShaderProgram::getUniformLocation("viewPos");

	location_spotLightPosition = ShaderProgram::getUniformLocation("light.position");
	location_spotLightDirection = ShaderProgram::getUniformLocation("light.direction");

	location_spotLightAmbient = ShaderProgram::getUniformLocation("light.ambient");
	location_spotLightDiffuse = ShaderProgram::getUniformLocation("light.diffuse");
	location_spotLightSpecular = ShaderProgram::getUniformLocation("light.specular");

	location_spotLightCutoff = ShaderProgram::getUniformLocation("light.cutOff");
	location_spotLightOuterCutoff = ShaderProgram::getUniformLocation("light.outerCutOff");

	location_spotLightConstant = ShaderProgram::getUniformLocation("light.constant");
	location_spotLightLinear = ShaderProgram::getUniformLocation("light.linear");
	location_spotLightQuadratic = ShaderProgram::getUniformLocation("light.quadratic");

	location_dirLightDirection = ShaderProgram::getUniformLocation("dirLight.direction");
	location_dirLightAmbient = ShaderProgram::getUniformLocation("dirLight.ambient");
	location_dirLightDiffuse = ShaderProgram::getUniformLocation("dirLight.diffuse");
	location_dirLightSpecular = ShaderProgram::getUniformLocation("dirLight.specular");

	for (int i = 0; i < 4; i++) {

		location_pointLightPosition[i] = ShaderProgram::getUniformLocation("pointLights[" + to_string(i) + "].position");

		location_pointLightConstant[i] = ShaderProgram::getUniformLocation("pointLights[" + to_string(i) + "].constant");
		location_pointLightLinear[i] = ShaderProgram::getUniformLocation("pointLights[" + to_string(i) + "].linear");
		location_pointLightQuadratic[i] = ShaderProgram::getUniformLocation("pointLights[" + to_string(i) + "].quadratic");

		location_pointLightAmbient[i] = ShaderProgram::getUniformLocation("pointLights[" + to_string(i) + "].ambient");
		location_pointLightDiffuse[i] = ShaderProgram::getUniformLocation("pointLights[" + to_string(i) + "].diffuse");
		location_pointLightSpecular[i] = ShaderProgram::getUniformLocation("pointLights[" + to_string(i) + "].specular");

	}

	lAnimated = ShaderProgram::getUniformLocation("animated");
	
		for (int i = 0; i < 100; i++) {
			std::ostringstream local;
	
			local << "gBones[" << i << "]";
			lgBones[i] = ShaderProgram::getUniformLocation(local.str());
		}

}

void AnimatedShader::connectMaps()
{
	ShaderProgram::loadInt(location_diffuseMap, 0);
	ShaderProgram::loadInt(location_specularMap, 1);
	ShaderProgram::loadInt(location_emissionMap, 2);
	ShaderProgram::loadInt(location_normalMap, 3);
}

void AnimatedShader::SetSpotLightProperties(vec3 pos, vec3 lightDirection, vec3 ambient, vec3 diffuse, vec3 specular, int lightDistance, float cutOff, float outerCutoff)
{
	vec3 K = lightConstants(lightDistance);

	ShaderProgram::loadFloat(location_spotLightConstant, K.x);
	ShaderProgram::loadFloat(location_spotLightLinear, K.y);
	ShaderProgram::loadFloat(location_spotLightQuadratic, K.z);
	ShaderProgram::loadVector(location_spotLightPosition, pos);
	ShaderProgram::loadVector(location_spotLightDirection, lightDirection);
	ShaderProgram::loadFloat(location_spotLightCutoff, cutOff);
	ShaderProgram::loadFloat(location_spotLightOuterCutoff, outerCutoff);
	ShaderProgram::loadVector(location_spotLightAmbient, ambient);
	ShaderProgram::loadVector(location_spotLightDiffuse, diffuse);
	ShaderProgram::loadVector(location_spotLightSpecular, specular);
}

void AnimatedShader::SetDirectionalLightProperties(vec3 dir, vec3 ambient, vec3 diffuse, vec3 specular)
{
	ShaderProgram::loadVector(location_dirLightDirection, dir);
	ShaderProgram::loadVector(location_dirLightAmbient, ambient);
	ShaderProgram::loadVector(location_dirLightDiffuse, diffuse);
	ShaderProgram::loadVector(location_dirLightSpecular, specular);
}

void AnimatedShader::SetPointLightProperties(int i, vec3 pos, vec3 ambient, vec3 diffuse, vec3 specular, int lightDistance)
{
	vec3 K = lightConstants(lightDistance);

	ShaderProgram::loadFloat(location_pointLightConstant[i], K.x);
	ShaderProgram::loadFloat(location_pointLightLinear[i], K.y);
	ShaderProgram::loadFloat(location_pointLightQuadratic[i], K.z);
	ShaderProgram::loadVector(location_pointLightPosition[i], pos);
	ShaderProgram::loadVector(location_pointLightAmbient[i], ambient);
	ShaderProgram::loadVector(location_pointLightDiffuse[i], diffuse);
	ShaderProgram::loadVector(location_pointLightSpecular[i], specular);
}


vec3 AnimatedShader::lightConstants(int dist)
{
	vec3 K = vec3();

	switch (dist) {
	case 7: K = vec3(1, 0.7, 1.8); break;
	case 13: K = vec3(1, 0.35, 0.44); break;
	case 20: K = vec3(1.0, 0.22, 0.20);  break;
	case 32: K = vec3(1.0, 0.14, 0.07);  break;
	case 50: K = vec3(1.0, 0.09, 0.032);  break;
	case 65: K = vec3(1.0, 0.07, 0.017);  break;
	case 100: K = vec3(1.0, 0.045, 0.0075);  break;
	case 160: K = vec3(1.0, 0.027, 0.0028);  break;
	case 200: K = vec3(1.0, 0.022, 0.0019);  break;
	case 325: K = vec3(1.0, 0.014, 0.0007);  break;
	case 600: K = vec3(1.0, 0.007, 0.0002);  break;
	case 3250: K = vec3(1.0, 0.0014, 0.000007);  break;
	default: K = vec3(1, 0.7, 1.8); break;
	}

	return K;
}

void AnimatedShader::materialProperties(float shininess)
{
	ShaderProgram::loadFloat(location_shineness, shininess);
}

void AnimatedShader::loadViewPos(vec3 cameraPos)
{
	ShaderProgram::loadVector(location_viewPos, cameraPos);
}

void AnimatedShader::loadTransformationMatrix(mat4 matrix)
{
	ShaderProgram::loadMatrix(location_transformationMatrix, matrix);
}

void AnimatedShader::loadProjectionMatrix(mat4 matrix)
{
	ShaderProgram::loadMatrix(location_projectionMatrix, matrix);
}

void AnimatedShader::loadViewMatrix(Camera camera)
{
	mat4 viewMatrix = Maths::createViewMatrix(camera);
	ShaderProgram::loadMatrix(location_viewMatrix, viewMatrix);
}



//#include "AnimatedShader.h"
//#include <string>
//#include <sstream>
//#include <GL/glew.h>
//#include <iostream>
//
//void AnimatedShader::LoadTransformationMatrix(mat4 matrix)
//{
//	loadMatrix(lTransMatrix, matrix);
//}
//
//void AnimatedShader::LoadProjectionMatrix(glm::mat4 matrix)
//{
//	loadMatrix(lProjMatrix, matrix);
//}
void AnimatedShader::LoadBoneMatrices(std::vector<glm::mat4> matrices) {
	for (int i = 0; i < 100; i++) {
		if (i < matrices.size()) {
			loadMatrix(lgBones[i], matrices[i]);
		}
		else {
			loadMatrix(lgBones[i], glm::mat4(1.f));
		}
	}
}
//
//void AnimatedShader::LoadShineVars(float damper, float shine) {
//	loadFloat(lShineDamper, damper);
//	loadFloat(lReflectivity, shine);
//}
//
//void AnimatedShader::LoadViewPos(vec3 pos)
//{
//	ShaderProgram::loadVector(lViewPos, pos);
//}
//
void AnimatedShader::LoadBoolAnimated(int value)
{
	loadInt(lAnimated, value);
}
//
//void AnimatedShader::LoadViewMatrix(Camera cam)
//{
//	glm::mat4 matrix = Maths::createViewMatrix(cam);
//	loadMatrix(lViewMatrix, matrix);
//}
//
//void AnimatedShader::LoadLight(DirectionalLight light) {
//	loadVector(lLightPosition, light.direction);
//	loadVector(lLightColor, light.ambient);
//}
//
//AnimatedShader::AnimatedShader() : ShaderProgram("shaders//av.txt", "shaders//af.txt") {
//	bindAttributes();
//	ShaderProgram::LinkAndValidateProgram();
//	getAllUniformLocations();
//};
//
//void AnimatedShader::bindAttributes() {
//	ShaderProgram::bindAttribute(0, "position");
//	ShaderProgram::bindAttribute(1, "textureCoords");
//	ShaderProgram::bindAttribute(2, "normal");
//	ShaderProgram::bindAttribute(3, "BoneIDs");
//	ShaderProgram::bindAttribute(4, "pesos");
//}
//
//void AnimatedShader::getAllUniformLocations()
//{
//	lTransMatrix = ShaderProgram::getUniformLocation("transformationMatrix");
//	lProjMatrix = ShaderProgram::getUniformLocation("projectionMatrix");
//	lViewMatrix = ShaderProgram::getUniformLocation("viewMatrix");
//	lLightPosition = ShaderProgram::getUniformLocation("lightPosition");
//	lLightColor = ShaderProgram::getUniformLocation("lightColor");
//	lShineDamper = ShaderProgram::getUniformLocation("shineDamper");
//	lReflectivity = ShaderProgram::getUniformLocation("reflectivity");
//	lAnimated = ShaderProgram::getUniformLocation("animated");
//	lViewPos = ShaderProgram::getUniformLocation("viewPos");
//
//	for (int i = 0; i < 100; i++) {
//		std::ostringstream local;
//
//		local << "gBones[" << i << "]";
//		lgBones[i] = ShaderProgram::getUniformLocation(local.str());
//	}
//}
