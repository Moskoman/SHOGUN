#pragma once

#include <unordered_map>
#include <vector>
#include <string>

#include "glm\glm.hpp"
#include <GL/glew.h>
#include "Light.h"
#include "RawModel.h"
#include "ModelTexture.h"
#include "Entity.h"
#include "AnimatedShader.h"
#include "Mesh.h"
#include "StaticMesh.h"

//TODO
/*
array de entidades ordenadas pelo eixo Z.
*/


class Renderer {
	/*static glm::mat4 projectionMatrix;
	static float FOV;
	static float NPLANE;
	static float FPLANE;
	static StaticShader* STATICSHADER;
	
	static AnimatedShader* ANIMATEDSHADER;
	static std::vector<Entity*> entities;*/
	

public:
	AnimatedShader * shader;
	Renderer(AnimatedShader * shader, mat4 projectionMatrix);
	void render(vector<Entity*> entities);
	void bindAttributes();
	void unbindAttributes();
	void prepareInstance(Entity * go);
	
	//static void Prepare();
	//static void Render(DirectionalLight sun, Camera camera, Mesh* mesh);
	//static void Render(DirectionalLight sun, Camera camera, IMesh* mesh, ShaderProgram* ss);
	//static void Render(DirectionalLight sun, Camera camera, Entity* entity);
	//static void Render(SpotLight spotLight, PointLight * pointLight, DirectionalLight directionalLight, Camera camera);
	//static void AddEntity(Entity* entity);

	////static void Render(Light sun, Camera camera, StaticMesh* mesh, AnimatedShader* ss);
	//static void CreateProjection(StaticShader* ss);
	//static void CreateProjection(AnimatedShader* as);
	
	/*static void CreateProjection(AnimatedModelShader* ss);
	static void RenderEntity(Entity* e, StaticShader* ss);
	static void AddEntity(Entity* e);
	static void Render(Light sun, Camera camera);
	static void RenderAnimatedModel(Light sun, Camera camera, AnimEntity am, AnimatedModelShader* ams);
	static void RenderNode(Node* node, AnimatedEntity* ae);
	static void RenderAnimated(Light sun, Camera camera, AnimatedEntity *ae);*/
	
};