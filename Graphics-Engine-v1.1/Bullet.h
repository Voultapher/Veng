#pragma once

#include <glm/glm.hpp>

#include "Object.h"

class Bullet : public Object
{
public:
	Bullet(glm::vec4 posAndSize, glm::vec2 direction, float speed, int lifeTime);
	~Bullet();

	bool update(); // retuns true when lifeTime is 0

private:
	int _lifeTime;
};

