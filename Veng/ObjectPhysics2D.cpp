#include "ObjectPhysics2D.h"

namespace Veng{

ObjectPhysics2D::ObjectPhysics2D()
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

void ObjectPhysics2D::init(glm::vec4 posAndSize, glm::vec2 direction, float speed){
	_speed = speed;
	_position = glm::vec2(posAndSize.x, posAndSize.y);
	_direction = direction;
	_posAndSize = posAndSize;
}

void ObjectPhysics2D::move(glm::vec2 direction){
	_position += direction * _speed;
}

void ObjectPhysics2D::setDirection(glm::vec2 direction){
	_direction = direction;
}

}