#pragma once
#include "Camera.h"
#include <unordered_map>
#include <vector>
#include "SkyboxShader.h"
#include "RawModel.h"
#include "Loader.h"

using namespace std;
using namespace glm;

class SkyboxRenderer
{
	
public:
	RawModel cube;
	int texture, texture2;
	SkyboxShader * shader;
	float time = 0;
	float cd = 5;
	SkyboxRenderer(SkyboxShader * shader, mat4 proj);
	~SkyboxRenderer();
	void render(Camera camera);
	void bindTextures();
};

