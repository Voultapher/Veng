#pragma once

#include <map>
#include <vector>
#include <glm/glm.hpp>

#include "ObjectPhysics2D.h"

namespace veng{

class Physics2D
{
public:
	Physics2D();
	~Physics2D();

	void reserveData(std::size_t objectCount);

	ObjectPhysics2D* addObject();
	glm::vec4* addPosAndBoundary(glm::vec4 posAndBoundary);
	// void deleteObject(ObjectPhysics2D* physicsObject); // currently 

	void update();

	std::vector<ObjectPhysics2D>* getObjects2D() { return &_physicsObjects; } // use uniqu_pntr ? // internal use only

private:
	std::vector<glm::vec4> _posAndBoundarys;
	std::vector<ObjectPhysics2D> _physicsObjects;

	std::vector<veng::ObjectPhysics2D* > findIntersection(ObjectPhysics2D& physicsObject);
	bool twoObjectIntersection(ObjectPhysics2D* physicsObjectA, ObjectPhysics2D* physicsObjectB);
	void collide(ObjectPhysics2D& objectA, std::vector<veng::ObjectPhysics2D*> collisionGroup);
};

}