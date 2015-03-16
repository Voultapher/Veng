#include "Bullet.h"

Bullet::Bullet(glm::vec4 posAndSize, glm::vec2 direction, float mass, float speed, float boundaryScale, int lifeTime)
{
	objectPhysics = new Veng::ObjectPhysics2D;
	objectPhysics->init(posAndSize, direction, mass, speed, boundaryScale);

	_lifeTime = lifeTime;
	
}


Bullet::~Bullet()
{
	delete objectPhysics;
}


bool Bullet::update(){
	_lifeTime--;
	if (_lifeTime == 0){
		return true;// should be true only false for test
	}
	return false;
}