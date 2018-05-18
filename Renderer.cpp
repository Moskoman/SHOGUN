#include "Renderer.h"
#include "Maths.h"
//
//glm::mat4 Renderer::projectionMatrix;
//float Renderer::FOV = 70;
//float Renderer::NPLANE = 0.1f;
//float Renderer::FPLANE = 100;
//
//StaticShader* Renderer::STATICSHADER = NULL;
//AnimatedShader* Renderer::ANIMATEDSHADER = NULL;
//
//std::vector<Entity*> Renderer::entities;
//
//
//void Renderer::Prepare() {
//
//	glEnable(GL_DEPTH_TEST);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//}
//
//void Renderer::Render(DirectionalLight sun, Camera camera, Mesh * mesh)
//{
//	Prepare();
//
//	STATICSHADER->start();
//
//	mesh->Render(ANIMATEDSHADER);
//
//	STATICSHADER->stop();
//}
//
///*void Renderer::Render(Light sun, Camera camera, Entity * mesh, std::vector<glm::mat4> transforms)
//{
//Prepare();
//
//STATICSHADER->Start();
//STATICSHADER->LoadLight(sun);
//STATICSHADER->LoadViewMatrix(camera);
//STATICSHADER->LoadBoneMatrices(transforms);
//
//glm::mat4 transformationMatrix = Math::TransformMatrix(mesh->GetPos(), mesh->GetRot(), mesh->GetScale());
//
//STATICSHADER->LoadTransformationMatrix(glm::mat4(transformationMatrix));
//
//mesh->GetMesh()->Render(STATICSHADER);
//
//STATICSHADER->Stop();
//}*/
//
//void Renderer::Render(DirectionalLight sun, Camera camera, IMesh* mesh, ShaderProgram* ss) {
//	Prepare();
//	if (mesh->type == IMesh::TYPE::STATIC) {
//		StaticShader* shader = (StaticShader*)ss;
//
//		shader->start();
//		shader->loadLight(sun);
//		shader->loadViewMatrix(camera);
//		shader->loadTransformationMatrix(glm::mat4(1.f));
//
//		mesh->Render(ss);
//
//		shader->stop();
//	}
//}
//
//void Renderer::Render(DirectionalLight sun, Camera camera, Entity * entity)
//{
//	//Prepare();
//	/*if (entity->GetMesh()->type == IMesh::TYPE::STATIC) {
//	StaticShader* shader = STATICSHADER;
//
//	shader->Start();
//	shader->LoadLight(sun);
//	shader->LoadViewMatrix(camera);
//
//	shader->LoadTransformationMatrix(Math::TransformMatrix(entity->GetPos(), entity->GetRot(), entity->GetScale()));
//
//	entity->GetMesh()->Render(shader);
//
//	shader->Stop();
//	}
//	else{
//	AnimatedShader* shader = ANIMATEDSHADER;
//
//	shader->Start();
//	shader->LoadLight(sun);
//	shader->LoadViewMatrix(camera);
//
//	//shader->LoadBoneMatrices(entity->GetMesh()->)
//
//	shader->LoadTransformationMatrix(Math::TransformMatrix(entity->GetPos(), entity->GetRot(), entity->GetScale()));
//
//	entity->GetMesh()->Render(shader);
//
//	shader->Stop();
//
//	}*/
//}
//
//void Renderer::Render(SpotLight spotLight, PointLight * pointLight, DirectionalLight directionalLight, Camera camera)
//{
//
//	//Renderer::Prepare();
//
//	ANIMATEDSHADER->start();
//
//	ANIMATEDSHADER->loadViewPos(camera.position);
//	ANIMATEDSHADER->materialProperties(5);
//	ANIMATEDSHADER->SetDirectionalLightProperties(directionalLight.direction, directionalLight.ambient, directionalLight.diffuse, directionalLight.specular);
//
//	for (int i = 0; i < 4; i++) {
//		ANIMATEDSHADER->SetPointLightProperties(i, pointLight[i].position, pointLight[i].ambient, pointLight[i].diffuse, pointLight[i].specular, pointLight[i].distance);
//	}
//
//	ANIMATEDSHADER->SetSpotLightProperties(spotLight.position, spotLight.direction, spotLight.ambient, spotLight.diffuse, spotLight.specular, spotLight.distance, spotLight.cutOff, spotLight.outerCutOff);
//
//	ANIMATEDSHADER->loadViewMatrix(camera);
//	
//	glEnableVertexAttribArray(0);
//	glEnableVertexAttribArray(1);
//	glEnableVertexAttribArray(2);
//	glEnableVertexAttribArray(3);
//	glEnableVertexAttribArray(4);
//
//	for (auto entity : entities) {
//		
//		
//		ANIMATEDSHADER->LoadBoneMatrices(entity->GetTransforms());
//		ANIMATEDSHADER->loadTransformationMatrix(Maths::createTransformationMatrix(entity->position, entity->rotation, entity->scale));
//		entity->GetMesh()->Render(ANIMATEDSHADER);
//	}
//
//	glDisableVertexAttribArray(0);
//	glDisableVertexAttribArray(1);
//	glDisableVertexAttribArray(2);
//	glDisableVertexAttribArray(3);
//	glDisableVertexAttribArray(4);
//
//	entities.clear();
//	ANIMATEDSHADER->stop();
//	/*for (auto entity : entities) {
//	if (entity->GetMesh()->type == IMesh::TYPE::STATIC) {
//	StaticShader* shader = STATICSHADER;
//
//	shader->Start();
//	shader->LoadLight(sun);
//	shader->LoadViewMatrix(camera);
//
//	shader->LoadTransformationMatrix(Math::TransformMatrix(entity->GetPos(), entity->GetRot(), entity->GetScale()));
//
//	entity->GetMesh()->Render(shader);
//
//	shader->Stop();
//	}
//	else {
//	AnimatedShader* shader = ANIMATEDSHADER;
//
//	shader->Start();
//	shader->LoadLight(sun);
//	shader->LoadViewMatrix(camera);
//
//	shader->LoadTransformationMatrix(Math::TransformMatrix(entity->GetPos(), entity->GetRot(), entity->GetScale()));
//
//	entity->GetMesh()->Render(shader);
//
//	shader->Stop();
//
//	}
//	}*/
//}
//
//void Renderer::AddEntity(Entity * entity)
//{
//	entities.emplace_back(entity);
//}
//
//void Renderer::CreateProjection(StaticShader* ss)
//{
//	STATICSHADER = ss;
//	projectionMatrix = Maths::createProjectionMatrix(FOV, NPLANE, FPLANE);
//	//glEnable(GL_CULL_FACE);
//	//glCullFace(GL_BACK);
//	ss->start();
//	ss->loadProjectionMatrix(projectionMatrix);
//	ss->stop();
//}
//
//void Renderer::CreateProjection(AnimatedShader * as)
//{
//	ANIMATEDSHADER = as;
//	projectionMatrix = Maths::createProjectionMatrix(FOV, NPLANE, FPLANE);
//	//glEnable(GL_CULL_FACE);
//	//glCullFace(GL_BACK);
//	as->start();
//
//	as->loadProjectionMatrix(projectionMatrix);
//	as->connectMaps();
//	as->stop();
//}
//
//
///*
//std::unordered_map<int, std::vector<Entity*>> Renderer::entities;
//
//
//
//
//void Renderer::CreateProjection(AnimatedModelShader* ams) {
//projectionMatrix = Math::ProjectionMatrix(FOV, (4. / 3.), NPLANE, FPLANE);
//glEnable(GL_CULL_FACE);
//glCullFace(GL_BACK);
//ams->Start();
//ams->LoadProjectionMatrix(projectionMatrix);
//ams->Stop();
//}
//
//void Renderer::RenderEntity(Entity* e, StaticShader* ss)
//{
//glBindVertexArray(e->GetModel().GetModel().GetvaoID());
//glEnableVertexAttribArray(0);
//glEnableVertexAttribArray(1);
//glEnableVertexAttribArray(2);
//
//glm::mat4 transformationMatrix = Math::TransformMatrix(e->GetPos(), e->GetRot(), e->GetScale());
//
//ss->LoadTransformationMatrix(glm::mat4(transformationMatrix));
//
//ss->LoadShineVars(e->GetModel().GetTexture().GetShineDamp(), e->GetModel().GetTexture().GetReflectivity());
//
//glActiveTexture(GL_TEXTURE0);
//glBindTexture(GL_TEXTURE_2D, e->GetModel().GetTexture().GetID());
//glDrawElements(GL_TRIANGLES, e->GetModel().GetModel().GetVertexCount(), GL_UNSIGNED_INT, 0);
//
//glDisableVertexAttribArray(2);
//glDisableVertexAttribArray(1);
//glDisableVertexAttribArray(0);
//glBindVertexArray(0);
//}
//
//void Renderer::AddEntity(Entity * e)
//{
//entities[e->GetModel().GetModel().GetvaoID()].emplace_back(e);
//}
//
//
//void Renderer::Render(Light sun, Camera camera)
//{
//Prepare();
//STATICSHADER->Start();
//STATICSHADER->LoadLight(sun);
//STATICSHADER->LoadViewMatrix(camera);
//
//for (auto i = entities.begin(); i != entities.end(); i++) {
//glBindVertexArray(i->first);
//glEnableVertexAttribArray(0);
//glEnableVertexAttribArray(1);
//glEnableVertexAttribArray(2);
//
//
//for (int j = 0; j < i->second.size(); j++) {
//Entity* e = i->second[j];
//
//glm::mat4 transformationMatrix = Math::TransformMatrix(e->GetPos(), e->GetRot(), e->GetScale());
//
//STATICSHADER->LoadTransformationMatrix(glm::mat4(transformationMatrix));
//
//STATICSHADER->LoadShineVars(e->GetModel().GetTexture().GetShineDamp(), e->GetModel().GetTexture().GetReflectivity());
//
//glActiveTexture(GL_TEXTURE0);
//glBindTexture(GL_TEXTURE_2D, e->GetModel().GetTexture().GetID());
//glDrawElements(GL_TRIANGLES, e->GetModel().GetModel().GetVertexCount(), GL_UNSIGNED_INT, 0);
//}
//
//glDisableVertexAttribArray(2);
//glDisableVertexAttribArray(1);
//glDisableVertexAttribArray(0);
//glBindVertexArray(0);
//}
//
//STATICSHADER->Stop();
//entities.clear();
//}
//
//
//
//void Renderer::RenderAnimatedModel(Light sun, Camera camera, AnimEntity ae, AnimatedModelShader* ams)
//{
//Prepare();
//
//AnimatedModel am = ae.model;
//
//glm::mat4 transformationMatrix = Math::TransformMatrix(ae.pos, ae.rot, ae.scale);
//
//ams->Start();
//
//ams->LoadJointTransforms(am.GetJointTransforms());
//
//glBindVertexArray(am.model.GetvaoID());
//glEnableVertexAttribArray(0);
//glEnableVertexAttribArray(1);
//glEnableVertexAttribArray(2);
//glEnableVertexAttribArray(3);
//glEnableVertexAttribArray(4);
//
//ams->LoadLight(sun);
//ams->LoadViewMatrix(camera);
//ams->LoadTransformationMatrix(transformationMatrix);
//
//glActiveTexture(GL_TEXTURE0);
//glBindTexture(GL_TEXTURE_2D, am.texture.GetID());
//glDrawElements(GL_TRIANGLES, am.model.GetVertexCount(), GL_UNSIGNED_INT, 0);
//
//glDisableVertexAttribArray(4);
//glDisableVertexAttribArray(3);
//glDisableVertexAttribArray(2);
//glDisableVertexAttribArray(1);
//glDisableVertexAttribArray(0);
//glBindVertexArray(0);
//ams->Stop();
//}
//
//void Renderer::RenderNode(Node * node, AnimatedEntity *ae)
//{
//std::vector<RawModel> rawModels = node->GetMeshes();
//
//for (auto rm : rawModels) {
//glBindVertexArray(rm.GetvaoID());
//glEnableVertexAttribArray(0);
//glEnableVertexAttribArray(1);
//glEnableVertexAttribArray(2);
//
//glm::mat4 transformationMatrix = Math::TransformMatrix(ae->GetPos(), ae->GetRot(), ae->GetScale());
//
//STATICSHADER->LoadTransformationMatrix(glm::mat4(transformationMatrix));
//STATICSHADER->LoadShineVars(ae->GetTexture().GetShineDamp(), ae->GetTexture().GetReflectivity());
//
//glActiveTexture(GL_TEXTURE0);
//glBindTexture(GL_TEXTURE_2D, ae->GetTexture().GetID());
//glDrawElements(GL_TRIANGLES, rm.GetVertexCount(), GL_UNSIGNED_INT, 0);
//
//glDisableVertexAttribArray(2);
//glDisableVertexAttribArray(1);
//glDisableVertexAttribArray(0);
//glBindVertexArray(0);
//}
//
//for (int i = 0; i < node->GetChildren().size(); i++) {
//RenderNode(node->GetChildren()[i], ae);
//}
//}


Renderer::Renderer(AnimatedShader * shader, mat4 projectionMatrix) : shader(shader)
{
	shader->start();
	shader->loadProjectionMatrix(projectionMatrix);
	shader->connectMaps();
	shader->stop();
}

void Renderer::render(vector<Entity*> entities)
{
	bindAttributes();

	for (auto entity : entities) {
		prepareInstance(entity);
		entity->GetMesh()->Render(shader);
	}

	unbindAttributes();
}

void Renderer::bindAttributes()
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
}

void Renderer::unbindAttributes()
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
	glBindVertexArray(0);
}

void Renderer::prepareInstance(Entity * go)
{
	glm::mat4 transformationMatrix = Maths::createTransformationMatrix(go->position, go->rotation, go->scale);
	shader->loadTransformationMatrix(transformationMatrix);
	shader->LoadBoolAnimated(go->GetMesh()->animated);
	shader->LoadBoneMatrices(go->transforms);
}
