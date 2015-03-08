#pragma once

#include <glm/glm.hpp>

#include "Object.h"

class Player : public Object
{
public:
	Player();
	~Player();

	void init(glm::vec4 posAndSize, glm::vec2 direction, float speed, float life);

private:
	float _life;

};

