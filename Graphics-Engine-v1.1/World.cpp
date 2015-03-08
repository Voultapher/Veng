#include "World.h"

World::World() :
_boundry(0.0f)
{
}


World::~World()
{
}

void World::init(glm::vec4 boundry){
	_boundry = boundry;
	_up = glm::vec2(0.0f, 1.0f);
	_down = glm::vec2(0.0f, -1.0f);
	_left = glm::vec2(-1.0f, 0.0f);
	_right = glm::vec2(1.0f, 0.0f);

}

bool World::ableToMove(glm::vec4 posAndSize, glm::vec2 &direction){
	if (posAndSize.y < _boundry.y){
		direction = glm::normalize(direction + _up);
		return false;
	}

	if ((posAndSize.y + posAndSize.w) > _boundry.w){
		direction = glm::normalize(direction + _down);
		return false;
	}

	if ((posAndSize.x + posAndSize.z) > _boundry.z){
		direction = glm::normalize(direction + _left);
		return false;
	}

	if (posAndSize.x < _boundry.x){
		direction = glm::normalize(direction + _right);
		return false;
	}
	return true;
}