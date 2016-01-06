#pragma once

#include <glm/glm.hpp>

#include <veng/ObjectPhysics2D.h>

class Player
{
public:
	Player();
	~Player();

	void init(float life, float movementSpeed, veng::ObjectPhysics2D* objectLink);

	veng::ObjectPhysics2D* objectPhysics;

	float getMovementSpeed() const { return _movementSpeed; }

private:
	float _life;
	float _movementSpeed;
};

