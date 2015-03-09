#include "Bullet.h"

Bullet::Bullet(glm::vec4 posAndSize, glm::vec2 direction, float speed, int lifeTime)
{
	objectPhysics.init(posAndSize, direction, speed);
	_lifeTime = lifeTime;
	
}


Bullet::~Bullet()
{
}


bool Bullet::update(){
	_lifeTime--;
	if (_lifeTime == 0){
		return true;
	}
	return false;
}