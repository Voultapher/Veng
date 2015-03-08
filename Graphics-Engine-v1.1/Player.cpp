#include "Player.h"

Player::Player()
{
}


Player::~Player()
{
}

void Player::init(glm::vec4 posAndSize, glm::vec2 direction, float speed, float life){
	_life = life;
	_speed = speed;
	_position = glm::vec2(posAndSize.x, posAndSize.y);
	_direction = direction;
	_posAndSize = posAndSize;
}