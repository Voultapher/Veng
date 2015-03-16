#include "PhysicsManager.h"

namespace Veng{

PhysicsManager::PhysicsManager()
{
}


PhysicsManager::~PhysicsManager()
{
}

void PhysicsManager::addPhysicsObject(ObjectPhysics2D* physicsObject2D){
	_physicsObjects2D.addObject(physicsObject2D);
}

void PhysicsManager::deletePhysicsObject(ObjectPhysics2D* physicsObject2D){
	_physicsObjects2D.deleteObject(physicsObject2D);
}

void PhysicsManager::update(){
	_physicsObjects2D.update();
}

ObjectPhysics2D* PhysicsManager::findIntersection(ObjectPhysics2D* physicsObject2D){
	return _physicsObjects2D.findIntersection(physicsObject2D);
}

void PhysicsManager::collide(ObjectPhysics2D* objectA, ObjectPhysics2D* objectB){
	_physicsObjects2D.collide(objectA, objectB);
}

}