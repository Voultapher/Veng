#include "PhysicsManager.h"

namespace veng{

PhysicsManager::PhysicsManager()
{
}


PhysicsManager::~PhysicsManager()
{
}

void PhysicsManager::init(std::size_t maxObjects, Render& render){
	_maxObjects = maxObjects;
	_physics2D.reserveData(maxObjects);
	render.linkRenderToPhysics(_physics2D.getObjects2D()); // somewhat frankenstein code
}

ObjectPhysics2D* PhysicsManager::addPhysicsObject(InitPackage2D& initPackage2D){
	ObjectPhysics2D* physicsObject2D = _physics2D.addObject();

	//glm::vec4* debug = _physics2D.addPosAndBoundary(initPackage2D.createPosAndBoundary());

	physicsObject2D->init(initPackage2D, _physics2D.addPosAndBoundary(initPackage2D.createPosAndBoundary())); // oops have fun reading this line
	
	return physicsObject2D;
}

void PhysicsManager::update(){
	_physics2D.update();
}

}