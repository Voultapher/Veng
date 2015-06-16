#include "Player.h"

Player::Player()
{
}


Player::~Player()
{
	delete objectPhysics;
}

void Player::init(float life, float movementSpeed){
	objectPhysics = new Veng::ObjectPhysics2D;

	_life = life;
	_movementSpeed = movementSpeed;
}