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

private:
	std::vector<ObjectPhysics2D*> _physicsObjects;

	std::vector<Veng::ObjectPhysics2D* > findIntersection(ObjectPhysics2D* physicsObject);
	void collide(ObjectPhysics2D* objectA, std::vector<Veng::ObjectPhysics2D* > collisionGroup);
};

}