#pragma once

#include <map>
#include <vector>
#include <glm/glm.hpp>

#include "ObjectPhysics2D.h"

namespace Veng{

class Physics2D
{
public:
	Physics2D();
	~Physics2D();

	void addObject(ObjectPhysics2D* physicsObject);

	void deleteObject(ObjectPhysics2D* physicsObject);

	void update();

	ObjectPhysics2D* findIntersection(ObjectPhysics2D* physicsObject);

	void collide(ObjectPhysics2D* objectA, ObjectPhysics2D* objectB);

private:
	std::vector<ObjectPhysics2D*> _physicsObjects;

	void collideA(ObjectPhysics2D* objectA, ObjectPhysics2D* objectB, glm::vec2 newMomentum);
};

}