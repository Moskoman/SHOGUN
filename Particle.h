#pragma once
#include <glm/glm.hpp>
#include "ParticleTexture.h"
#include "Camera.h"
using namespace glm;

class Particle
{
public:
	vec3 position;
	vec3 velocity;
	float gravityEffect;
	float gravity;
	float lifeLength;
	float rotation;
	float scale;
	float elapsedTime = 0;
	ParticleTexture texture;
	float distance;
	vec2 texOffset1;
	vec2 texOffset2;
	float blend;

	Particle(ParticleTexture &texture, vec3 pos, vec3 vel, float gravity, float gravityEffect, float lifeLength, float rotation, float scale);
	bool Update(float dt, Camera camera);

	void UpdateTextureCoordInfo();
	void setTextureOffset(vec2 offset, int index);
	~Particle();

};

