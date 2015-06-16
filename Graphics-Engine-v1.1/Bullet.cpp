#include "Bullet.h"

Bullet::Bullet(int lifeTime)
{
	objectPhysics = new Veng::ObjectPhysics2D;

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