#include "ModelTexture.h"
#include "Debug.h"


ModelTexture::ModelTexture() : textureID(0)
{
}

ModelTexture::ModelTexture(GLuint texture):textureID(texture), shineDamper(1), reflectivity(0), hasTransparency(false), useFakeLighting(false), rows(1)
{
	Debug2("Model Texture", texture);
}


ModelTexture::~ModelTexture()
{
}
