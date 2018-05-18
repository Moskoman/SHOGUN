#pragma once
#include "RawModel.h"
#include "Loader.h"
#include "GUITexture.h"
#include <glm\glm.hpp>
#include "GUIShader.h"

using namespace glm;
using namespace std;

class GUIRenderer
{
public:
	GUIShader * shader;
	RawModel quad;
	GUIRenderer();
	void render(vector<GUITexture> guis);
	~GUIRenderer();
};

