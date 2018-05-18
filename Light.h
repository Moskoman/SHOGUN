#pragma once
#include <glm\glm.hpp>
#include <string>
#include "Debug.h"

using namespace std;
using namespace glm;

class Light
{
public:
	vec3 ambient, diffuse, specular;

	Light(vec3 ambient, vec3 diffuse, vec3 specular) : 
		ambient(ambient), diffuse(diffuse), specular(specular) {}

	~Light() { }

	virtual bool isType(string type) = 0;

};


class DirectionalLight : public Light
{
public:
	vec3 direction;

	DirectionalLight(vec3 direction, vec3 ambient, vec3 diffuse, vec3 specular) :
		Light(ambient, diffuse, specular), direction(direction) {}

	bool isType(string type) { return type == "DirectionalLight"; }

	~DirectionalLight() {}
};

class PointLight : public Light
{
public:
	vec3 position;
	int distance;

	PointLight(vec3 position, int distance, vec3 ambient, vec3 diffuse, vec3 specular) :
		Light(ambient, diffuse, specular), position(position), distance(distance) {}

	bool isType(string type) { return type == "PointLight"; }


	~PointLight() {}
};


class SpotLight : public Light
{
public:
	vec3 direction;
	int distance;
	vec3 position;

	float cutOff;
	float outerCutOff;

	SpotLight(vec3 position, vec3 direction, int distance, float cutOff, float outerCutOff, vec3 ambient, vec3 diffuse, vec3 specular) :
	Light(ambient, diffuse, specular), position(position), distance(distance), cutOff(cutOff), outerCutOff(outerCutOff), direction(direction) {}

	bool isType(string type) { return type == "SpotLight"; }

	~SpotLight() {}

};