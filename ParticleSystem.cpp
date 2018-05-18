#include "ParticleSystem.h"




ParticleSystem::ParticleSystem(ParticleTexture &texture, float pps, float speed, float gravityComplient, float lifeLength)
	:texture(texture), pps(pps), speed(speed), gravityComplient(gravityComplient), lifeLength(lifeLength)
{

	Debug2("Psystem", texture.textureID);
}

void ParticleSystem::Update(float dt, vec3 center)
{
	float particlesToCreate = pps * dt;
	int count = glm::floor(particlesToCreate);
	//float partialParticle = (int) particlesToCreate % 1;
	
	for (int i = 0; i < count; i++) {
		EmitParticle(center);
	}
}

void ParticleSystem::EmitParticle(vec3 center)
{

	vec3 velocity = vec3(((float)(rand()%30-10))/10.0, 1, 0);
	velocity = glm::normalize(velocity);
	velocity = velocity * (speed);
	Particle(texture, center + vec3((float)(rand()%80-40)/100.0, 0, (float)(rand() % 80 - 40) / 100.0), velocity, -10 , gravityComplient, lifeLength, rand()%360, float(rand()%25+1)/10.0);
}

ParticleSystem::~ParticleSystem()
{
}
