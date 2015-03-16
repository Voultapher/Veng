#include "ObjectPhysics2D.h"

namespace Veng{

	ObjectPhysics2D::ObjectPhysics2D() :
	_dimension(2)
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

void ObjectPhysics2D::init(glm::vec4 posAndSize, glm::vec2 direction, float mass, float speed, float boundaryScale){
	_speed = speed;
	_mass = mass;
	_position = glm::vec2(posAndSize.x, posAndSize.y);
	_direction = direction;
	_posAndSize = posAndSize;

	_boundray.x = posAndSize.z * boundaryScale;
	_boundray.y = posAndSize.w * boundaryScale;
	_posAndBoundary.z = _boundray.x;
	_posAndBoundary.w = _boundray.y;
}

void ObjectPhysics2D::move(glm::vec2 direction){
	_position += direction * _speed;
}

void ObjectPhysics2D::setDirection(glm::vec2 direction){
	_direction = direction;
}

void ObjectPhysics2D::setSpeed(float speed){
	_speed = speed;
}

}