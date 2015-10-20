#include "Bullet.h"

Bullet::Bullet(int lifeTime, Veng::ObjectPhysics2D* objectLink)
{
	objectPhysics = objectLink;
	_lifeTime = lifeTime;
	
}


Bullet::~Bullet()
{
}


bool Bullet::update(){
	_lifeTime--;
	if (_lifeTime == 0){
		return true;// should be true only false for test
	}
	return false;
}