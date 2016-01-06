#pragma once

#include <vector>

#include "ObjectPhysics2D.h"
#include "Physics2D.h"
#include "InitPackage2D.h"
#include "Render.h"
#include "GROC.h"


namespace veng{

class PhysicsManager
{
public:

	PhysicsManager();
	~PhysicsManager();

	void init(std::size_t maxObjects, Render& render);

	ObjectPhysics2D* addPhysicsObject(InitPackage2D& initPackage2D);

	/*template<typename T>
	void deleteObject(T& physicsObject){ // this is templated as I expect more than one sort of physicsobject
		if (physicsObject->getDimension() == 2){
			_physicsObjects2D.deleteObject(physicsObject);
		}
	}*/

	void update();

private:
	unsigned int _maxObjects;

	Physics2D _physics2D;
};

}