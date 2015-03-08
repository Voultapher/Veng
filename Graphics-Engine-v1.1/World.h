#pragma once

#include <glm/glm.hpp>

class World
{
public:
	World();
	~World();

	void init(glm::vec4 boundry);

	bool ableToMove(glm::vec4 posAndSize, glm::vec2 &direction);

private:
	glm::vec2 _up;
	glm::vec2 _down;
	glm::vec2 _left;
	glm::vec2 _right;
	glm::vec4 _boundry;
};

