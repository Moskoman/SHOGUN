#include "RawModel.h"

RawModel::RawModel() : vaoID(0), vertexCount(0)
{
}

RawModel::RawModel(GLuint vaoID, int vertexCount): vaoID(vaoID), vertexCount(vertexCount)
{
}

RawModel::~RawModel()
{
}
