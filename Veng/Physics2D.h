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

	void reserveData(unsigned int objectCount);

	ObjectPhysics2D* addObject();
	glm::vec4* addPosAndBoundary(glm::vec4 posAndBoundary);
	// void deleteObject(ObjectPhysics2D* physicsObject); // currently 

	void update();

	std::vector<ObjectPhysics2D>* getObjects2D() { return &_physicsObjects; } // use uniqu_pntr ? // internal use only

private:
	std::vector<glm::vec4> _posAndBoundarys;
	std::vector<ObjectPhysics2D> _physicsObjects;

	std::vector<Veng::ObjectPhysics2D* > findIntersection(ObjectPhysics2D& physicsObject);
	bool twoObjectIntersection(ObjectPhysics2D* physicsObjectA, ObjectPhysics2D* physicsObjectB);
	void collide(ObjectPhysics2D& objectA, std::vector<Veng::ObjectPhysics2D*> collisionGroup);
};

}