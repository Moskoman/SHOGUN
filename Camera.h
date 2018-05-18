#pragma once
#include <glm\glm.hpp>

class Camera
{
public:
	glm::vec3 position;
	float pitch;
	float yaw;
	float roll;

	void move(glm::vec3 pos){position += pos;}
	Camera() : position(glm::vec3(0, 0, 0)), yaw(0), pitch(0){}
	Camera(glm::vec3 position) : position(position), yaw(0), pitch(0){}
	~Camera(){}
};

