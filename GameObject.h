#pragma once

class GameObject {
protected:
	bool remove;
public:
	GameObject() {};
	~GameObject() {};
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	bool Remove() { return remove; };
};