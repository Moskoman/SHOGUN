#include "GUIRenderer.h"

#include "Maths.h"

GUIRenderer::GUIRenderer() 
{
	vector<vec2> positions = {
		vec2(-1,1),
		vec2(-1,-1),
		vec2(1,1),
		vec2(1,-1)
	};
	shader = new GUIShader();

	quad = Loader::loadToVAO(positions);

}

void GUIRenderer::render(vector<GUITexture> guis)
{
	shader->start();
	glBindVertexArray(quad.vaoID);
	glEnableVertexAttribArray(0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);

	for (int i = 0; i < guis.size(); i++) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, guis[i].textureID);
		mat4 matrix = Maths::createTransformationMatrix(guis[i].position, guis[i].scale);
		shader->loadTransformationMatrix(matrix);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, quad.vertexCount);
	}
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	shader->stop();
}

GUIRenderer::~GUIRenderer()
{
}
