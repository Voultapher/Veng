#pragma once

#include <vector>

#include "ObjectPhysics2D.h"
#include "Physics2D.h"
#include "PhysicsInitPackage2D.h"

namespace Veng{

class PhysicsManager
{
public:
	PhysicsManager();
	~PhysicsManager();

	void addPhysicsObject(ObjectPhysics2D* physicsObject2D, PhysicsInitPackage2D& physicsInitPackage2D);

	template<typename T>
	void deleteObject(T& physicsObject){ // this is templated as I expect more than one sort of physicsobject
		if (physicsObject->getDimension() == 2){
			_physicsObjects2D.deleteObject(physicsObject);
		}
	}

	void update();

private:
	Physics2D _physicsObjects2D;
};

}