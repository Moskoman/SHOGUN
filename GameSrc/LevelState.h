#pragma once

#include <SDL.h>
#include <glm\glm.hpp>
#include "../Game.h"
#include "../State.h"
#include "../Camera.h"
#include "../Loader.h"
#include "../MasterRenderer.h"
#include "../GUITexture.h"
#include "../GUIRenderer.h"
#include "../Mesh.h"
#include "../Movie.h"
#include "../GameObjectTest.h"
#include "../Renderer.h"
#include "../Light.h"
#include "../InputManager.h"
#include <glm\gtx\rotate_vector.hpp>
#include "../ParticleSystem.h"

using namespace glm;
using namespace std;

class LevelState : public State {



	PointLight pt[4] = {
		PointLight(vec3(-4, 0, 20),		13,		vec3(1, 1,1)*0.0f,	vec3(1, 1,1)*0.0f,	vec3(1, 1,1)*0.0f),
		PointLight(vec3(1, 0, -10),		13,		vec3(1, 1,1)*0.0f,	vec3(1, 1,1)*0.0f,	vec3(1, 1,1)*0.0f),
		PointLight(vec3(0, -1, -10),	13,		vec3(1, 1,1)*0.0f,	vec3(1, 1,1)*0.0f,	vec3(1, 1,1)*0.0f),
		PointLight(vec3(0, -2, 10),		13,		vec3(1, 1,1)*0.0f,	vec3(1, 1,1)*0.0f,	vec3(1, 1,1)*0.0f)
	};
	DirectionalLight direct = DirectionalLight(vec3(0, 0, -1), vec3(1, 1, 1)*1.0f, vec3(1, 1, 1)*0.6f, vec3(1, 1, 1)*10.0f);


	Camera camera = Camera(vec3(0, 0, -4));

	SpotLight sl = SpotLight(camera.position, vec3(0, 0, -1), 13, glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(17.5f)), vec3(1, 1, 1)*0.0f, vec3(1, 1, 1)*0.0f, vec3(1, 1, 1)*0.0f);


public:
	LevelState() {};
	~LevelState();

	void Update(float dt) {};

	void Render() {
	
		MasterRenderer::GetInstance().render(sl, pt, direct, camera);
	};
};