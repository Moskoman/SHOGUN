#include "ParticleRenderer.h"
#include "Debug.h"
#include "Loader.h"
#include <glm\gtc\matrix_transform.hpp>

ParticleRenderer::ParticleRenderer(ParticleShader * shader, mat4 proj): shader(shader)
{
	vector<vec2> VERTICES = { vec2(-0.5f, 0.5f), vec2(-0.5f, -0.5f), vec2(0.5f, 0.5f), vec2(0.5f, -0.5f) };


	quad = Loader::loadToVAO(VERTICES);

	shader->start();
	shader->loadProjectionMatrix(proj);
	shader->stop();



}

ParticleRenderer::~ParticleRenderer()
{
}

void ParticleRenderer::updateModelViewMatrix(vec3 pos, float rotation, float scale, mat4 view) {
	glm::mat4 matrix(1);
	matrix = glm::translate(matrix, pos);

	matrix[0][0] = view[0][0];
	matrix[1][0] = view[0][1];
	matrix[2][0] = view[0][2];

	matrix[0][1] = view[1][0];
	matrix[1][1] = view[1][1];
	matrix[2][1] = view[1][2];

	matrix[0][2] = view[2][0];
	matrix[1][2] = view[2][1];
	matrix[2][2] = view[2][2];

	matrix = rotate(matrix, glm::radians(rotation), glm::vec3(0, 0, 1));
	matrix = glm::scale(matrix, vec3(scale, scale, scale));

	mat4 mvm = view * matrix;

	shader->loadModelViewMatrix(mvm);

}

void ParticleRenderer::render(unordered_map<ParticleTexture, vector<Particle>> particles, Camera camera)
{
	mat4 viewMatrix = Maths::createViewMatrix(camera);
	prepare();

	for (auto&& it : particles) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, it.first.textureID);
		
		for (int i = 0; i < it.second.size(); i++) {
			updateModelViewMatrix(it.second[i].position, it.second[i].rotation, it.second[i].scale, viewMatrix);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, quad.vertexCount);

			shader->loadTextureCoordInfo(it.second[i].texOffset1, it.second[i].texOffset2, it.first.numberOfRows, it.second[i].blend);
		}
	}
	

	finishRendering();
}

void ParticleRenderer::cleanUp()
{
}

void ParticleRenderer::prepare()
{
	shader->start();
	glBindVertexArray(quad.vaoID);
	glEnableVertexAttribArray(0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glDepthMask(false);


}

void ParticleRenderer::finishRendering()
{
	glDepthMask(true);
	glDisable(GL_BLEND);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	shader->stop();
	
}
