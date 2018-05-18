#pragma once

#include <SDL.h>
#include <glm\glm.hpp>
#include "Game.h"
#include "State.h"
#include "Camera.h"
#include "Loader.h"
#include "MasterRenderer.h"
#include "GUITexture.h"
#include "GUIRenderer.h"
#include "Mesh.h"
#include "Movie.h"
#include "GameObjectTest.h"
#include "Renderer.h"
#include "Light.h"
#include "InputManager.h"
#include <glm\gtx\rotate_vector.hpp>
#include "ParticleSystem.h"

using namespace glm;
using namespace std;

class TestState : public State {

	PointLight pt[4] = {
		PointLight(vec3(-4, 0, 20),		13,		vec3(1, 1,1)*0.0f,	vec3(1, 1,1)*0.0f,	vec3(1, 1,1)*0.0f),
		PointLight(vec3(1, 0, -10),		13,		vec3(1, 1,1)*0.0f,	vec3(1, 1,1)*0.0f,	vec3(1, 1,1)*0.0f),
		PointLight(vec3(0, -1, -10),	13,		vec3(1, 1,1)*0.0f,	vec3(1, 1,1)*0.0f,	vec3(1, 1,1)*0.0f),
		PointLight(vec3(0, -2, 10),		13,		vec3(1, 1,1)*0.0f,	vec3(1, 1,1)*0.0f,	vec3(1, 1,1)*0.0f)
	};

	SpotLight sl = SpotLight(camera.position, vec3(0, 0, -1), 13, glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(17.5f)), vec3(1, 1, 1)*0.0f, vec3(1, 1, 1)*0.0f, vec3(1, 1, 1)*0.0f);
	DirectionalLight direct = DirectionalLight(vec3(0, 0, -1), vec3(1, 1, 1)*1.0f, vec3(1, 1, 1)*0.6f, vec3(1, 1, 1)*10.0f);
	ParticleSystem * ps;

	Camera camera = Camera(vec3(0, 0, -4));

	int i = 0;
	vector<GUITexture> guiTextures;
	GUIRenderer guirenderer = GUIRenderer(); //agrupar no masterRenderer
	vec3 pos = vec3(1, 0, 0);
public:

	TestState() {

		ParticleTexture ptexture = ParticleTexture(Loader::LoadTexture2("res/s.png"), 1);
		ps = new ParticleSystem(ptexture, 60, 8, 1, 5.0);
		AddGameObject(new GameObjectTest(Entity(Loader::LoadModel("res/models/fixed.obj"), glm::vec3(0, -0, 0), glm::vec3(0, 0, 0), 0.25)));

		guiTextures.emplace_back(GUITexture(Loader::LoadTexture2("res/GUI/gui.png"), vec2(0.75f, 0.90f), vec2(0.22f, 0.1f)));
		

	}


	void Update(float dt) {

		MasterRenderer::GetInstance().updateAllParticles(dt, camera);
		float delta = 0.2f;
		for (unsigned int i = 0; i < gameObjects.size(); i++) {
			gameObjects[i]->Update(dt);
		}

		ps->Update(dt, vec3(-0.15f, -4.5f, -19.8f));

		/*if (InputManager::GetInstance().IsKeyDown(SDLK_h)) {
			Particle(glm::vec3(0, -5, -20), vec3(0, 20, 0), -10, 1, 4, 0, 1);
		}*/

		if (InputManager::GetInstance().IsKeyDown(SDLK_UP)) {
			camera.position -= vec3(0, 0, 1)*delta;
		}

		if (InputManager::GetInstance().IsKeyDown(SDLK_DOWN)) {
			camera.position += vec3(0, 0, 1)*delta;
		}

		if (InputManager::GetInstance().IsKeyDown(SDLK_w)) {
			camera.position += vec3(0, 1, 0)*delta;
		}

		if (InputManager::GetInstance().IsKeyDown(SDLK_s)) {
			camera.position -= vec3(0, 1, 0)*delta;
		}

		if (InputManager::GetInstance().IsKeyDown(SDLK_LEFT)) {
			camera.position -= vec3(1, 0, 0)*delta;
		}

		if (InputManager::GetInstance().IsKeyDown(SDLK_RIGHT)) {
			camera.position += vec3(1, 0, 0)*delta;
		}

		if (InputManager::GetInstance().IsKeyDown(SDLK_ESCAPE)) {
			remove = true;
		}

		if (InputManager::GetInstance().KeyPress(SDLK_a)) {
			Movie::playfile("res/videos/vf.ogv", Game::GetInstance()->window, Game::GetInstance()->renderer);
		}

		pos = rotateY(pos, radians(5.0f));
		//Debugv(pos);
		sl = SpotLight(camera.position, vec3(0, 0, -1), 65, glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(17.5f)), vec3(1, 1, 1)*0.6f, vec3(1, 1, 1), vec3(1, 1, 1));
		direct = DirectionalLight(pos, vec3(1, 1, 1)*1.0f, vec3(1, 1, 1)*0.5f, vec3(1, 1, 1)*0.5f);

	}

	void Render() {
		for (unsigned int i = 0; i < gameObjects.size(); i++) {
			gameObjects[i]->Render();
		}
		MasterRenderer::GetInstance().render(sl, pt, direct, camera);
		guirenderer.render(guiTextures);
	}

};