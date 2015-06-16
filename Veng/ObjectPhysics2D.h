#pragma once

#include <glm/glm.hpp>

#include "PhysicsInitPackage2D.h"

namespace Veng{

class ObjectPhysics2D
{
public:
	ObjectPhysics2D();
	~ObjectPhysics2D();

	void init(PhysicsInitPackage2D& initPackage);

	void move();
	void setAcceleration(glm::vec2 acceleration);
	void addAcceleration(glm::vec2 acceleration);
	void applyForce(glm::vec2 force);
	void pushBack();
	void pushBackAndStop();
	void lock();
	void unLock();

	void setSpeed(glm::vec2 speed);
	void setSpeedZero();

	bool isLocked() const { return _locked; }
	int getDimension() const { return _dimension; }
	glm::vec2 getSpeed() const { return _speed; }
	float getSpeedMagnitude();
	glm::vec2 getAcceleration() const { return _acceleration; }
	float getMass() const { return _mass; }
	float getFriction() const { return _friction; }
	glm::vec2 getPosition() const { return _position; }
	glm::vec2 getMomentum() { return _speed * _mass; }
	glm::vec4 getPosAndSize();
	glm::vec4 getPosAndBoundary();
	glm::vec4 getNextPosAndBoundary();

private:
	bool _locked;
	int _dimension;
	glm::vec2 _acceleration;
	glm::vec2 _speed;
	float _maxSpeed;
	float _mass;
	float _friction;

	glm::vec2 _position;
	glm::vec4 _posAndSize;
	glm::vec4 _posAndBoundary;
	glm::vec2 _boundray;
};

}