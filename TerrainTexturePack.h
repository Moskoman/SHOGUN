#pragma once 
#include "ModelTexture.h"
class TerrainTexturePack
{
public:
	GLuint backgroundTexture, r,g,b;
	TerrainTexturePack(GLuint backgroundTexture, GLuint r, GLuint g, GLuint b);
	~TerrainTexturePack();
};

