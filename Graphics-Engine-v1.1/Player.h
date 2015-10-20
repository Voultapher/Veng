#pragma once

#include <glm/glm.hpp>

#include <Veng/ObjectPhysics2D.h>

class Player
{
public:
	Player();
	~Player();

	void init(float life, float movementSpeed, Veng::ObjectPhysics2D* objectLink);

	Veng::ObjectPhysics2D* objectPhysics;

	float getMovementSpeed() const { return _movementSpeed; }

private:
	float _life;
	float _movementSpeed;
};

