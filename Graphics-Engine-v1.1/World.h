#pragma once

#include <glm/glm.hpp>

class World
{
public:
	World();
	~World();

	void init(glm::vec4 boundry);

	bool outOfBound(glm::vec4 posAndSize);
	float getSize() const { return _worldsize; }

private:

	float _worldsize;
	glm::vec2 _up;
	glm::vec2 _down;
	glm::vec2 _left;
	glm::vec2 _right;
	glm::vec4 _boundary;
};

