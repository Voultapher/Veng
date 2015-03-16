#pragma once

#include <vector>

#include "ObjectPhysics2D.h"
#include "Physics2D.h"

namespace Veng{

class PhysicsManager
{
public:
	PhysicsManager();
	~PhysicsManager();

	void addPhysicsObject(ObjectPhysics2D* physicsObject2D);

	void deletePhysicsObject(ObjectPhysics2D* physicsObject2D);

	void update();

	ObjectPhysics2D* findIntersection(ObjectPhysics2D* physicsObject2D);

	void collide(ObjectPhysics2D* objectA, ObjectPhysics2D* objectB);

private:
	Physics2D _physicsObjects2D;
};

}