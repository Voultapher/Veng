#include "Object.h"


Object::Object()
{
}


Object::~Object()
{
}

glm::vec4 Object::getPosAndSize(){
	_posAndSize.x = _position.x;
	_posAndSize.y = _position.y;
	return _posAndSize;
}

void Object::init(glm::vec4 posAndSize, glm::vec2 direction, float speed){
	_speed = speed;
	_position = glm::vec2(posAndSize.x, posAndSize.y);
	_direction = direction;
	_posAndSize = posAndSize;
}

void Object::move(glm::vec2 _direction){
	_position += _direction * _speed;
}