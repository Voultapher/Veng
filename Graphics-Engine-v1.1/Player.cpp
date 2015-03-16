#include "Player.h"

Player::Player()
{
}


Player::~Player()
{
	delete objectPhysics;
}

void Player::init(glm::vec4 posAndSize, glm::vec2 direction, float mass, float speed, float boundaryScale, float life){
	objectPhysics = new Veng::ObjectPhysics2D;
	objectPhysics->init(posAndSize, direction, mass, 0.0f, boundaryScale);
	_life = life;
	_movementSpeed = speed;
}