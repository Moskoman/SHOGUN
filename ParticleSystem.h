#pragma once
#include "Particle.h"
#include "MasterRenderer.h"

class ParticleSystem
{
public:
	float pps;
	float speed;
	float gravityComplient;
	float lifeLength;

	ParticleTexture texture;

	ParticleSystem(ParticleTexture &texture, float pps, float speed, float gravityComplient, float lifeLength);

	void Update(float dt, vec3 center);
	void EmitParticle(vec3 center);

	~ParticleSystem();
};

