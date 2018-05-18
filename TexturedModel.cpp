#include "TexturedModel.h"
#include "Debug.h"


TexturedModel::TexturedModel(RawModel model, ModelTexture modelTexture, ModelTexture specular, ModelTexture emission,  ModelTexture normal): rawModel(model), texture(modelTexture), emission(emission), specular(specular), normal(normal)
{
	Debug3("Texture " << texture.textureID, "Texture Specular " << specular.textureID, "Texture Emission " << emission.textureID);

}

TexturedModel::TexturedModel(RawModel model, ModelTexture texture): rawModel(model), texture(texture)
{

	Debug4("TexturedModel criado", "VaoID " << rawModel.vaoID,  "VERTEXCOUNT " << rawModel.vertexCount, "Texture " << texture.textureID);
}


TexturedModel::~TexturedModel()
{
}
