#pragma once
#include <vector>
#include <string>

#include <GL/glew.h>

#include "ModelTexture.h"
#include "ShaderProgram.h"

class IMesh {
protected:
	struct MeshEntry {
		MeshEntry() :baseVertex(0), baseIndex(0), numIndices(0), materialIndex(0) {};
		unsigned int baseVertex; //Vertex Buffer
		unsigned int baseIndex; //Index Buffer

		unsigned int numIndices;
		unsigned int materialIndex;
	};

	virtual bool Initialize(std::string filename) = 0;

	unsigned int VAO;

	std::vector<MeshEntry> mEntries;
	std::vector<ModelTexture*> mTextures;

public:
	IMesh() { VAO = 0; };
	~IMesh() { if (VAO) glDeleteVertexArrays(1, &VAO); };

	virtual void Render(ShaderProgram* sp) = 0;
	virtual void Update(float dt) = 0;
	enum TYPE {
		STATIC, ANIMATED
	};
	TYPE type;
};