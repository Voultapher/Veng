#pragma once

#include <glm/glm.hpp>

class Bullet
{
public:
	Bullet(glm::vec4 posAndSize, glm::vec2 direction, float speed, int lifeTime);
	~Bullet();

	glm::vec2 getPosition() const { return _position; }
	glm::vec2 getDirection() const { return _direction; }
	glm::vec4 getPosAndSize();

	bool update(); // retuns true when lifeTime is 0

private:
	int _lifeTime;
	float _speed;
	glm::vec2 _position;
	glm::vec2 _direction;
	glm::vec4 _posAndSize;
};

