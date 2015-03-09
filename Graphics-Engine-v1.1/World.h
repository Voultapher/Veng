#pragma once

#include <glm/glm.hpp>

class World
{
public:
	World();
	~World();

	void init(glm::vec4 boundry);

	bool outOfBound(glm::vec4 posAndSize, glm::vec2 &direction);

private:
	glm::vec2 safeVecAdd(glm::vec2 vecA, glm::vec2 vecB);

	glm::vec2 _up;
	glm::vec2 _down;
	glm::vec2 _left;
	glm::vec2 _right;
	glm::vec4 _boundry;
};

