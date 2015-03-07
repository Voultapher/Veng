#include "Player.h"

Player::Player()
{
}


Player::~Player()
{
}

glm::vec4 Player::getPosAndSize(){
	_posAndSize.x = _position.x;
	_posAndSize.y = _position.y;
	return _posAndSize;
}

void Player::init(glm::vec4 posAndSize, glm::vec2 direction, float speed, float life){
	_life = life;
	_speed = speed;
	_position = glm::vec2(posAndSize.x, posAndSize.y);
	_direction = direction;
	_posAndSize = posAndSize;
}