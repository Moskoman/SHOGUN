#pragma once
#include "ParticleShader.h"
#include "RawModel.h"
#include "Particle.h"
#include <vector>
#include "ParticleTexture.h"
#include <unordered_map>

class ParticleRenderer
{
public:
	RawModel quad;
	ParticleShader * shader;

	ParticleRenderer(ParticleShader * shader, mat4 proj);
	~ParticleRenderer();
	void updateModelViewMatrix(vec3 pos, float rotation, float scale, mat4 view);
	void render(unordered_map<ParticleTexture, vector<Particle>> particles, Camera camera);
	void cleanUp();
	void prepare();
	void finishRendering();
};

