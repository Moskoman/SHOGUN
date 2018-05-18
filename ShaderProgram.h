#pragma once

#include<string>
#include <GL\glew.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>

using namespace std;

class ShaderProgram
{
public:
	void start();
	void stop();
	virtual void getAllUniformLocations() = 0;
	virtual void bindAttributes() = 0;

	ShaderProgram(string vertexFile, string fragmentFile);
	~ShaderProgram();
	GLuint LoadShader(string file, GLenum type);

	void bindAttribute(GLuint attribute, string variableName);
protected:
	string vertexFile, fragmentFile;
	GLuint programID;
	GLuint vertexShaderID;
	GLuint fragmentShaderID;
	string ReadFile(string file);
	void LinkAndValidateProgram();
	GLint getUniformLocation(string uniformName);
	void loadInt(GLint location, GLint value);
	void loadFloat(GLint location, GLfloat value);
	void loadVector4D(GLint location, glm::vec4 vector);
	void loadVector(GLint location, glm::vec3 vector);
	void load2DVector(GLint location, glm::vec2 vector);
	void loadBoolean(GLint location, GLboolean value);
	void loadMatrix(GLint location, glm::mat4 matrix);

};

