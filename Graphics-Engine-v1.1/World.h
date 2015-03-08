#pragma once

#include <glm/glm.hpp>

class World
{
public:
	World();
	~World();

	void init(glm::vec4 boundry);

	bool ableToMove(glm::vec2 position);

private:
	glm::vec4 _boundry;
};

