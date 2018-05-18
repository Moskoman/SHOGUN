#pragma once
#include <GL/glew.h>

using namespace std;

class RawModel
{
public:
	RawModel();
	RawModel(GLuint vaoID, int vertexCount);
	~RawModel();
	GLuint vaoID;
	int vertexCount;
};

