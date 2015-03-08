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
}

bool World::ableToMove(glm::vec2 position){
	if ((position.x > _boundry.z) || (position.y > _boundry.w) || (position.x < _boundry.x) || (position.y < _boundry.y)){
		return false;
	}
	return true;
}