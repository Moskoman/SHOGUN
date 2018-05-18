#include "GUIShader.h"
#include "Debug.h"


GUIShader::GUIShader() :ShaderProgram("shaders//gui.vs", "shaders//gui.fs")
{
	bindAttributes();
	ShaderProgram::LinkAndValidateProgram();
	getAllUniformLocations();
}

GUIShader::~GUIShader()
{
}

void GUIShader::bindAttributes() {
	bindAttribute(0, "position");
}

void GUIShader::getAllUniformLocations() {
	location_transformationMatrix = ShaderProgram::getUniformLocation("transformationMatrix");
}

void GUIShader::loadTransformationMatrix(mat4 matrix)
{
	ShaderProgram::loadMatrix(location_transformationMatrix, matrix);
}


