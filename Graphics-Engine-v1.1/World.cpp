#include "World.h"

World::World() :
_boundary(0.0f)
{
}


World::~World()
{
}

void World::init(glm::vec4 boundry){
	_worldsize = boundry.z;
	_boundary = boundry;
	_up = glm::vec2(0.0f, 1.0f);
	_down = glm::vec2(0.0f, -1.0f);
	_left = glm::vec2(-1.0f, 0.0f);
	_right = glm::vec2(1.0f, 0.0f);

}

bool World::outOfBound(glm::vec4 posAndSize){

	if (posAndSize.y < _boundary.y){
		return true;
	}

	if ((posAndSize.y + posAndSize.w) > _boundary.w){
		return true;
	}

	if ((posAndSize.x + posAndSize.z) > _boundary.z){
		return true;
	}

	if (posAndSize.x < _boundary.x){
		return true;
	}
	return false;
}
