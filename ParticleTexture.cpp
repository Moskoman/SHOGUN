#include "ParticleTexture.h"
#include "Debug.h"

ParticleTexture::ParticleTexture(int textureID, int numberOfRows) : textureID(textureID), numberOfRows(numberOfRows)
{
	Debug3("ParticleTexture", textureID, numberOfRows);
}

ParticleTexture::~ParticleTexture()
{
}
