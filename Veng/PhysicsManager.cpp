#include "PhysicsManager.h"

namespace Veng{

PhysicsManager::PhysicsManager()
{
}


PhysicsManager::~PhysicsManager()
{
}

void PhysicsManager::addPhysicsObject(ObjectPhysics2D* physicsObject2D, PhysicsInitPackage2D& physicsInitPackage2D){
	_physicsObjects2D.addObject(physicsObject2D);
	physicsObject2D->init(physicsInitPackage2D);
}

void PhysicsManager::update(){
	_physicsObjects2D.update();
}

}