#include "ObjectPhysics2D.h"

namespace Veng{

ObjectPhysics2D::ObjectPhysics2D() :
	_locked(false),
	_dimension(2),
	_acceleration(0.0f),
	_lowerSpeedTreshold(1e-5f)
{
}


ObjectPhysics2D::~ObjectPhysics2D()
{
}

glm::vec4 ObjectPhysics2D::getPosAndSize(){
	_posAndSize.x = _posAndBoundary->x;
	_posAndSize.y = _posAndBoundary->y;
	return _posAndSize;
}

glm::vec4 ObjectPhysics2D::getPosAndBoundary(){
	return *_posAndBoundary;
}

glm::vec4 ObjectPhysics2D::getNextPosAndBoundary(){
	return glm::vec4(_posAndBoundary->x + _speed.x, _posAndBoundary->y + _speed.y, _posAndBoundary->z, _posAndBoundary->w);
}

void ObjectPhysics2D::init(InitPackage2D& initPackage, glm::vec4* posAndBoundaryLink){
	_texture = initPackage.texture;
	_speed = initPackage.speed;
	_mass = initPackage.mass;
	_friction = initPackage.friction;
	_stationary = initPackage.stationanry;

	_posAndSize = getAdjustedPosAndSize(initPackage.posAndSize, initPackage.orientationFlag);
	_posAndBoundary = posAndBoundaryLink;
}

float ObjectPhysics2D::getSpeedMagnitude(){
	float speed = glm::length(_speed);
	if (speed < 0.0f){
		speed *= -1.0f;
	}
	return speed;
}

void ObjectPhysics2D::move(){
	if (_stationary == false){
		_speed += _acceleration;
		_acceleration = glm::vec2(0.0f);

		_speed *= _friction;
		_posAndBoundary->x += _speed.x;
		_posAndBoundary->y += _speed.y;
	}

}

void ObjectPhysics2D::undoMovement(){
	if (_stationary == false){
		_posAndBoundary->x -= _speed.x;
		_posAndBoundary->y -= _speed.y;
	}
}

void ObjectPhysics2D::pushBack(){ // causes corner Problems
	if (_stationary == false){
		_posAndBoundary->x -= _posAndSize.z / 50.0f;
		_posAndBoundary->y -= _posAndSize.w / 50.0f;
	}
}

void ObjectPhysics2D::pushBackAndStop(){
	if (_stationary == false){
		_posAndBoundary->x -= _speed.x;
		_posAndBoundary->y -= _speed.y;
		_speed = glm::vec2(0.0f);
		_acceleration = glm::vec2(0.0f);
	}
}

void ObjectPhysics2D::suckToCenter(){ // causes center problems
	if (_stationary == false){
		_posAndBoundary->x *= 0.98f;
		_posAndBoundary->y *= 0.98f;
	}
}

void ObjectPhysics2D::pushOut(){ // causes center problems
	if (_stationary == false){
		_posAndBoundary->x *= 1.02f;
		_posAndBoundary->y *= 1.02f;
	}
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

void ObjectPhysics2D::setPosition(glm::vec2 position){
	if (_stationary == false){
		_posAndBoundary->x = position.x;
		_posAndBoundary->y = position.y;
	}
}

}