#pragma once

#include <glm/glm.hpp>

#include <Veng/ObjectPhysics2D.h>

class Player
{
public:
	Player();
	~Player();

	void init(glm::vec4 posAndSize, glm::vec2 direction, float mass, float speed, float boundaryScale, float life);

	Veng::ObjectPhysics2D* objectPhysics;

	float getMovementSpeed() const { return _movementSpeed; }

private:
	float _life;
	float _movementSpeed;
};

