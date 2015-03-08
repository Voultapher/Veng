#pragma once

#include <glm/glm.hpp>

class Object
{
public:
	Object();
	~Object();

	virtual void init(glm::vec4 posAndSize, glm::vec2 direction, float speed);

	virtual void move(glm::vec2 direction);
	void setDirection(glm::vec2 direction);

	float getSpeed() const { return _speed; }
	glm::vec2 getPosition() const { return _position; }
	glm::vec2 getDirection() const { return _direction; }
	glm::vec4 getPosAndSize();

protected:
	float _speed;
	glm::vec2 _position;
	glm::vec2 _direction;
	glm::vec4 _posAndSize;
};

