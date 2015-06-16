#include "ObjectPhysics2D.h"

namespace Veng{

ObjectPhysics2D::ObjectPhysics2D() :
	_locked(false),
	_dimension(2),
	_acceleration(0.0f)
{
}


ObjectPhysics2D::~ObjectPhysics2D()
{
}

glm::vec4 ObjectPhysics2D::getPosAndSize(){
	_posAndSize.x = _position.x;
	_posAndSize.y = _position.y;
	return _posAndSize;
}

glm::vec4 ObjectPhysics2D::getPosAndBoundary(){
	_posAndBoundary.x = _position.x;
	_posAndBoundary.y = _position.y;
	return _posAndBoundary;
}

glm::vec4 ObjectPhysics2D::getNextPosAndBoundary(){
	return glm::vec4(_position.x + _speed.x, _position.y + _speed.y, _boundray.x, _boundray.y);
}

void ObjectPhysics2D::init(PhysicsInitPackage2D& initPackage){
	_speed = initPackage.speed;
	_mass = initPackage.mass;
	_position = glm::vec2(initPackage.posAndSize.x, initPackage.posAndSize.y);
	_posAndSize = initPackage.posAndSize;

	_boundray.x = initPackage.posAndSize.z * initPackage.boundaryScale;
	_boundray.y = initPackage.posAndSize.w * initPackage.boundaryScale;
	_posAndBoundary.z = _boundray.x;
	_posAndBoundary.w = _boundray.y;

	_friction = initPackage.friction;
}

float ObjectPhysics2D::getSpeedMagnitude(){
	float speed = glm::length(_speed);
	if (speed < 0.0f){
		speed *= -1.0f;
	}
	return speed;
}

void ObjectPhysics2D::move(){

	_speed += _acceleration;
	_acceleration = glm::vec2(0.0f);

	_speed *= _friction;

	_position += _speed;
}

void ObjectPhysics2D::pushBack(){
	_position -= _speed;
}

void ObjectPhysics2D::pushBackAndStop(){
	_position -= _speed;
	_speed = glm::vec2(0.0f);
	_acceleration = glm::vec2(0.0f);
}

void ObjectPhysics2D::lock(){
	_locked = true;
}

void ObjectPhysics2D::unLock(){
	_locked = false;
}

void ObjectPhysics2D::addAcceleration(glm::vec2 acceleration){
	_acceleration += acceleration;
}

void ObjectPhysics2D::setAcceleration(glm::vec2 acceleration){
	_acceleration = acceleration;
}

void ObjectPhysics2D::applyForce(glm::vec2 force){
	_acceleration += force / _mass;
}

void ObjectPhysics2D::setSpeed(glm::vec2 speed){
	_speed = speed;
}

void ObjectPhysics2D::setSpeedZero(){
	_speed = glm::vec2(0.0f);
}

}