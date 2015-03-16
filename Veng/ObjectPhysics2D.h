#pragma once

#include <glm/glm.hpp>

namespace Veng{

class ObjectPhysics2D
{
public:
	ObjectPhysics2D();
	~ObjectPhysics2D();

	void init(glm::vec4 posAndSize, glm::vec2 direction, float mass, float speed, float boundaryScale);

	void move(glm::vec2 direction);
	void setDirection(glm::vec2 direction);
	void setSpeed(float speed);

	int getDimension() const { return _dimension; }
	float getSpeed() const { return _speed; }
	float getMass() const { return _mass; }
	glm::vec2 getPosition() const { return _position; }
	glm::vec2 getDirection() const { return _direction; }
	glm::vec2 getMomentum() { return _speed * _mass * _direction; }
	glm::vec4 getPosAndSize();
	glm::vec4 getPosAndBoundary();

private:
	int _dimension;
	float _speed;
	float _mass;
	glm::vec2 _position;
	glm::vec2 _direction;
	glm::vec4 _posAndSize;
	glm::vec4 _posAndBoundary;
	glm::vec2 _boundray;
};

}