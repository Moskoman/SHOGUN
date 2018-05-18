#include "SkyboxRenderer.h"
#include <glm/gtx/compatibility.hpp>
#include "Game.h"

SkyboxRenderer::SkyboxRenderer(SkyboxShader * shader, mat4 projectionMatrix): shader(shader)
{
	float SIZE = 500;

	vector<string> TEXTURE_FILES = { "res/skybox/night/nightRight.png", "res/skybox/night/nightLeft.png", "res/skybox/night/nightTop.png", "res/skybox/night/nightBottom.png", "res/skybox/night/nightBack.png", "res/skybox/night/nightFront.png" };
	vector<string> TEXTURE_FILES2 = { "res/skybox/right.png", "res/skybox/left.png", "res/skybox/top.png", "res/skybox/bottom.png", "res/skybox/back.png", "res/skybox/front.png" };

	vector<vec3> VERTICES = {
		vec3(-SIZE,  SIZE, -SIZE),
		vec3(-SIZE, -SIZE, -SIZE),
		vec3(SIZE, -SIZE, -SIZE),
		vec3(SIZE, -SIZE, -SIZE),
		vec3(SIZE,  SIZE, -SIZE),
		vec3(-SIZE,  SIZE, -SIZE),

		vec3(-SIZE, -SIZE,  SIZE),
		vec3(-SIZE, -SIZE, -SIZE),
		vec3(-SIZE,  SIZE, -SIZE),
		vec3(-SIZE,  SIZE, -SIZE),
		vec3(-SIZE,  SIZE,  SIZE),
		vec3(-SIZE, -SIZE,  SIZE),

		vec3(SIZE, -SIZE, -SIZE),
		vec3(SIZE, -SIZE,  SIZE),
		vec3(SIZE,  SIZE,  SIZE),
		vec3(SIZE,  SIZE,  SIZE),
		vec3(SIZE,  SIZE, -SIZE),
		vec3(SIZE, -SIZE, -SIZE),

		vec3(-SIZE, -SIZE,  SIZE),
		vec3(-SIZE,  SIZE,  SIZE),
		vec3(SIZE,  SIZE,  SIZE),
		vec3(SIZE,  SIZE,  SIZE),
		vec3(SIZE, -SIZE,  SIZE),
		vec3(-SIZE, -SIZE,  SIZE),

		vec3(-SIZE,  SIZE, -SIZE),
		vec3(SIZE,  SIZE, -SIZE),
		vec3(SIZE,  SIZE,  SIZE),
		vec3(SIZE,  SIZE,  SIZE),
		vec3(-SIZE,  SIZE,  SIZE),
		vec3(-SIZE,  SIZE, -SIZE),

		vec3(-SIZE, -SIZE, -SIZE),
		vec3(-SIZE, -SIZE,  SIZE),
		vec3(SIZE, -SIZE, -SIZE),
		vec3(SIZE, -SIZE, -SIZE),
		vec3(-SIZE, -SIZE,  SIZE),
		vec3(SIZE, -SIZE,  SIZE)
	};

	cube = Loader::loadToVAO(VERTICES);

	Debug(cube.vaoID << " test " << cube.vertexCount);

	Debug(SIZE);

	Debug(SIZE);

	Debug(SIZE);
	for(int i=0; i < 36; i++)
		Debugv(VERTICES[i])

	texture = Loader::LoadCubeMap(TEXTURE_FILES);
	texture2 = Loader::LoadCubeMap(TEXTURE_FILES2);
	Debug(texture);
	

	shader->start();
	shader->connectTextureUnits();
	shader->loadProjectionMatrix(projectionMatrix);
	shader->stop();

}


SkyboxRenderer::~SkyboxRenderer()
{
}

void SkyboxRenderer::render(Camera camera) {
	shader->start();
	shader->loadViewMatrix(camera);
	glBindVertexArray(cube.vaoID);
	glEnableVertexAttribArray(0);
	bindTextures();



	time += Game::GetInstance()->GetDeltaTime();
	float t = time / cd;
	float smoothstep = t * t*t * (t * (6.0f*t - 15.0f) + 10.0f);

	shader->LoadBlend(lerp(0.0f, 1.0f, smoothstep));
		
	if (time >= cd) {
		int temp = texture;
		texture = texture2;
		texture2 = temp;
		time = 0;
	}

	glDrawArrays(GL_TRIANGLES, 0, cube.vertexCount);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	shader->stop();
}

void SkyboxRenderer::bindTextures() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture2);

	
}
