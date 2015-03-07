#pragma once

#include <glm/glm.hpp>

class Player
{
public:
	Player();
	~Player();

	void init(glm::vec4 posAndSize, glm::vec2 direction, float speed, float life);

	void movePlayer(glm::vec2 direction, float speed);

	glm::vec2 getPosition() const { return _position; }
	glm::vec2 getDirection() const { return _direction; }
	glm::vec4 getPosAndSize();

private:
	float _life;
	float _speed;
	glm::vec2 _position;
	glm::vec2 _direction;
	glm::vec4 _posAndSize;

};

