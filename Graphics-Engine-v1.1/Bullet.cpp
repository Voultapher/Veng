#include "Bullet.h"
#include <Veng/GLTexture.h>
#include <Veng/ResourceManager.h>


Bullet::Bullet(glm::vec2 position, glm::vec2 direction, float speed, int lifeTime)
{
	_lifeTime = lifeTime;
	_position = position;
	_direction = direction;
	_speed = speed;
}


Bullet::~Bullet()
{
}

void Bullet::draw(Veng::SpriteBatch&  spriteBatch){
	glm::vec4 posAndSize(_position.x, _position.y, 30.0f, 30.0f);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static Veng::GLTexture texture = Veng::ResourceManager::getTexture("Textures/Player/p1_hurt.png"); //this is bad
	Veng::Color color;
	color.setColor(220, 218, 148, 255);

	spriteBatch.draw(posAndSize, uv, texture.id, 0.0f, color);
}

bool Bullet::update(){
	_position += _direction * _speed;
	_lifeTime--;
	if (_lifeTime == 0){
		return true;
	}
	return false;
}
