#pragma once

#include <glm/glm.hpp>

#include <Veng/ObjectPhysics2D.h>

class Bullet
{
public:
	Bullet(glm::vec4 posAndSize, glm::vec2 direction, float speed, int lifeTime);
	~Bullet();

	Veng::ObjectPhysics2D objectPhysics;

	bool update(); // retuns true when lifeTime is 0

private:
	int _lifeTime;
};

