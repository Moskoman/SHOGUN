#pragma once

#include <GL/glew.h>
#include <glm\glm.hpp>

using namespace glm;

class ModelTexture
{
public:
	float shineDamper;
	float reflectivity;
	bool hasTransparency;
	bool  useFakeLighting;

	int rows;
		
	GLuint textureID;

	ModelTexture();
	ModelTexture(GLuint textureID);
	~ModelTexture();
};

