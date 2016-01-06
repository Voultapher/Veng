#pragma once

#include <glm/glm.hpp>

#include <veng/ObjectPhysics2D.h>

class Bullet
{
public:
	Bullet(int lifeTime, veng::ObjectPhysics2D* objectLink);
	~Bullet();

	veng::ObjectPhysics2D* objectPhysics;

	bool update(); // retuns true when lifeTime is 0

private:
	int _lifeTime;
};

