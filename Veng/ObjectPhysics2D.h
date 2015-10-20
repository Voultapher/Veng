#pragma once

#include <glm/glm.hpp>

#include "InitPackage2D.h"
#include "Orientation2D.h"

namespace Veng{

class ObjectPhysics2D
{
public:
	ObjectPhysics2D();
	~ObjectPhysics2D();

	void init(InitPackage2D& initPackage, glm::vec4* posAndBoundaryLink);

	void move();
	void setAcceleration(glm::vec2 acceleration);
	void addAcceleration(glm::vec2 acceleration);
	void applyForce(glm::vec2 force);
	void undoMovement();
	void pushBack();
	void pushBackAndStop();
	void suckToCenter();
	void pushOut();
	void lock();
	void unLock();

	void setSpeed(glm::vec2 speed);
	void setSpeedZero();
	void setPosition(glm::vec2 position);

	GLTexture getTexture() const { return _texture; }

	bool isLocked() const { return _locked; }
	int getDimension() const { return _dimension; }
	glm::vec2 getSpeed() const { return _speed; }
	float getSpeedMagnitude();
	glm::vec2 getAcceleration() const { return _acceleration; }
	float getMass() const { return _mass; }
	float getFriction() const { return _friction; }
	glm::vec2 getPosition() const { return glm::vec2(_posAndBoundary->x, _posAndBoundary->y); }
	glm::vec2 getMomentum() { return _speed * _mass; }
	glm::vec4 getPosAndSize();
	glm::vec4 getPosAndBoundary();
	glm::vec4 getNextPosAndBoundary();

private:
	bool _locked;
	bool _stationary;
	int _dimension;
	glm::vec2 _acceleration;
	glm::vec2 _speed;
	float _maxSpeed;
	float _mass;
	float _friction;
	float _lowerSpeedTreshold;

	GLTexture _texture;

	glm::vec4 _posAndSize;
	glm::vec4* _posAndBoundary;
};

}