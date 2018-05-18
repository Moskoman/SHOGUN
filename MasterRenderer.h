#pragma once
#include "Entity.h"
#include "Camera.h"
#include "TerrainRenderer.h"
#include "Light.h"
#include <unordered_map>
#include <vector>
#include "Renderer.h"
#include "SkyboxRenderer.h"
#include "ParticleShader.h"
#include "ParticleRenderer.h"
using namespace std;
class MasterRenderer
{	
public:
	float FOV = 70;
	float NEAR_PLANE = 0.1f;
	float FAR_PLANE = 1000;

	vec3 color;

	glm::mat4 projectionMatrix;
	void createProjectionMatrix();
	vector<Entity*> entities;
	//vector<Particle> particles;

	unordered_map<ParticleTexture, vector<Particle>> particless;

	//unordered_map<Mesh, vector<Entity>> entities;
	//unordered_map<TexturedModel, vector<Entity>> entities;
	//vector<Terrain> terrains;
	//StaticShader * entityShader;
	//IsaacShader * isaacShader;
	//IsaacRenderer * isaacRenderer;
	//EntityRenderer * entityRenderer;
	//TerrainRenderer * terrainRenderer;
	//TerrainShader * terrainShader;
	Renderer *renderer;
	SkyboxRenderer *sbRenderer;
	AnimatedShader *animatedShader;
	ParticleShader *particleShader;
	SkyboxShader *skyboxShader;
	ParticleRenderer *pRenderer;
	static void enableCulling();
	static void disableCulling();
	void render(SpotLight sun, PointLight * point, DirectionalLight dl, Camera camera);

	void processEntity(Entity* go);

	void processTerrain(Terrain terrain);

	void cleanUp();

	void prepare();

	static MasterRenderer& GetInstance() {
		static MasterRenderer masterRenderer;
		return masterRenderer;
	}

	void updateAllParticles(float dt, Camera camera);
	
	void AddParticle(Particle & particle);


	MasterRenderer();
	~MasterRenderer();
};

