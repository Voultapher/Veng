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

bool World::outOfBound(glm::vec4 posAndSize, glm::vec2 &direction){

	if (posAndSize.y < _boundry.y){
		direction.y = -direction.y;
		return true;
	}

	if ((posAndSize.y + posAndSize.w) > _boundry.w){
		direction.y = -direction.y;
		return true;
	}

	if ((posAndSize.x + posAndSize.z) > _boundry.z){
		direction.x = -direction.x;
		return true;
	}

	if (posAndSize.x < _boundry.x){
		direction.x = -direction.x;
		return true;
	}
	return false;
}

glm::vec2 World::safeVecAdd(glm::vec2 vecA, glm::vec2 vecB){
	glm::vec2 newVec = vecA + vecB;
	if (newVec == glm::vec2(0.0f, 0.0f)){
		newVec = vecB;
	}
	else{
		newVec = glm::normalize(newVec);
	}
	
	return newVec;
}