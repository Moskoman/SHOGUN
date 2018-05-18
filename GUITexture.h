#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>
using namespace glm;

class GUITexture
{
public:
	GLuint textureID;
	vec2 position, scale;
	GUITexture(GLuint textureID, vec2 pos, vec2 scale);
	~GUITexture();
};

