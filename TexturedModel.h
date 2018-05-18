#pragma once
#include <GL/glew.h>
#include "RawModel.h"
#include "ModelTexture.h"
#include "OBJLoader.h"

using namespace std;



class TexturedModel
{
public:
	RawModel rawModel;
	ModelTexture texture;
	ModelTexture emission, specular;
	ModelTexture normal;

	TexturedModel(RawModel model, ModelTexture modelTexture, ModelTexture emission, ModelTexture specular, ModelTexture normal);
	TexturedModel(RawModel model, ModelTexture modelTexture);
	~TexturedModel();

	bool operator==(const TexturedModel &other) const
	{
		return (rawModel.vaoID == other.rawModel.vaoID
			&& texture.textureID == other.texture.textureID);
	}
};

namespace std
{
	template <>
	struct hash<TexturedModel>
	{
		size_t operator()(const TexturedModel& k) const
		{
			return ((hash<uint>()(k.rawModel.vaoID) ^ (hash<uint>()(k.texture.textureID) << 1)) >> 1);
		}
	};
}