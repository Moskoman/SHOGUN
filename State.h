#pragma once

#include <vector>
#include <memory>
#include "GameObject.h"

class State {
protected:
	std::vector<std::unique_ptr<GameObject>> gameObjects;

	bool remove;

public:
	State() { remove = false; };
	~State() { gameObjects.clear(); };

	bool ShouldRemove() { return remove; };

	void AddGameObject(GameObject* go) { gameObjects.emplace_back(go); };
	
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
};