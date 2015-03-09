#pragma once

#include <glm/glm.hpp>

#include <Veng/ObjectPhysics2D.h>

class Player
{
public:
	Player();
	~Player();

	void init(glm::vec4 posAndSize, glm::vec2 direction, float speed, float life);

	Veng::ObjectPhysics2D objectPhysics;

private:
	float _life;

};

