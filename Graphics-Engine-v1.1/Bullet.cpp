#include "Bullet.h"


Bullet::Bullet(glm::vec4 posAndSize, glm::vec2 direction, float speed, int lifeTime)
{
	_lifeTime = lifeTime;
	_speed = speed;
	_position = glm::vec2(posAndSize.x, posAndSize.y);
	_direction = direction;
	_posAndSize = posAndSize;
	
}


Bullet::~Bullet()
{
}

glm::vec4 Bullet::getPosAndSize(){
	_posAndSize.x = _position.x;
	_posAndSize.y = _position.y;
	return _posAndSize;
}

bool Bullet::update(){
	_position += _direction * _speed;
	_lifeTime--;
	if (_lifeTime == 0){
		return true;
	}
	return false;
}
