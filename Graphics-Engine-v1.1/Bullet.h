#pragma once

#include <glm/glm.hpp>j
#include <Veng/SpriteBatch.h>

class Bullet
{
public:
	Bullet(glm::vec2 position, glm::vec2 direction, float speed, int lifeTime);
	~Bullet();

	void draw(Veng::SpriteBatch&  spriteBatch);
	bool update(); // retuns true when lifeTime is 0

private:
	int _lifeTime;
	float _speed;
	glm::vec2 _position;
	glm::vec2 _direction;
};

