#pragma once
#include "GameObject.h"
#include "MasterRenderer.h"
class GameObjectTest : public GameObject {
public:
	Entity entity;
	GameObjectTest(Entity entity);
	~GameObjectTest();
	void Update(float dt);
	void Render();
};