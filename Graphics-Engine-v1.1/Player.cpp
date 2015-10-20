#include "Player.h"

Player::Player()
{
}


Player::~Player()
{
	delete objectPhysics;
}

void Player::init(float life, float movementSpeed, Veng::ObjectPhysics2D* objectLink){
	objectPhysics = objectLink;

	_life = life;
	_movementSpeed = movementSpeed;
}