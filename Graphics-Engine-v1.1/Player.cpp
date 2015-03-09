#include "Player.h"

Player::Player()
{
}


Player::~Player()
{
}

void Player::init(glm::vec4 posAndSize, glm::vec2 direction, float speed, float life){
	objectPhysics.init(posAndSize, direction, speed);
	_life = life;
}