#include "Physics2D.h"

#include <cstdlib>

#include "Errors.h"

namespace Veng{

Physics2D::Physics2D()
{
}


Physics2D::~Physics2D()
{
}


void Physics2D::addObject(ObjectPhysics2D* physicsObject){

	_physicsObjects.push_back(physicsObject);

}

void Physics2D::deleteObject(ObjectPhysics2D* physicsObject){ // bad O(n)
	for (int i = 0; i < _physicsObjects.size(); i++){
		if (physicsObject == _physicsObjects[i]){
			_physicsObjects[i] = _physicsObjects.back();
			_physicsObjects.pop_back();
		}
	}
}

void Physics2D::update(){

	for (auto& physicsObject : _physicsObjects){ // first move every object without considering collision, to achieve move certainty
			physicsObject->move();
	}

	for (auto& physicsObject : _physicsObjects){ // unlock every object for the next iteration
		if (physicsObject->isLocked() == false){
			std::vector<Veng::ObjectPhysics2D* > intersectingObjects = findIntersection(physicsObject);
			if (intersectingObjects.size() > 0){
				collide(physicsObject, intersectingObjects);
			}
		}
	}

	for (auto& physicsObject : _physicsObjects){
		physicsObject->unLock();
	}
}

std::vector<Veng::ObjectPhysics2D* > Physics2D::findIntersection(ObjectPhysics2D* physicsObject){ // naive implementation O(n^2)
	glm::vec4 posAndSize = physicsObject->getPosAndBoundary();
	std::vector<Veng::ObjectPhysics2D* > intersectingObjects;

	int physicsObjectsSize = _physicsObjects.size();

	for (int i = 0; i < physicsObjectsSize; i++){
		if (_physicsObjects[i] != physicsObject){ // prevents finding itself
			glm::vec4 posAndSizeNearX = _physicsObjects[i]->getPosAndBoundary();
			if ((posAndSize.x > posAndSizeNearX.x && (posAndSize.x < (posAndSizeNearX.x + posAndSizeNearX.z)))
				|| ((posAndSize.x + posAndSize.z) > posAndSizeNearX.x && ((posAndSize.x + posAndSize.z) < (posAndSizeNearX.x + posAndSizeNearX.z)))){
				if ((posAndSize.y > posAndSizeNearX.y && posAndSize.y < (posAndSizeNearX.y + posAndSizeNearX.w))
					|| ((posAndSize.y + posAndSize.w)> posAndSizeNearX.y && (posAndSize.y + posAndSize.w) < (posAndSizeNearX.y + posAndSizeNearX.w))){
					intersectingObjects.push_back(_physicsObjects[i]);
				}
			}
		}
	}

	return intersectingObjects;
}

bool Physics2D::twoObjectIntersection(ObjectPhysics2D* physicsObjectA, ObjectPhysics2D* physicsObjectB){
	glm::vec4 posAndSize = physicsObjectA->getPosAndBoundary();
	glm::vec4 posAndSizeNearX = physicsObjectB->getPosAndBoundary();
	if ((posAndSize.x > posAndSizeNearX.x && (posAndSize.x < (posAndSizeNearX.x + posAndSizeNearX.z)))
		|| ((posAndSize.x + posAndSize.z) > posAndSizeNearX.x && ((posAndSize.x + posAndSize.z) < (posAndSizeNearX.x + posAndSizeNearX.z)))){
		if ((posAndSize.y > posAndSizeNearX.y && posAndSize.y < (posAndSizeNearX.y + posAndSizeNearX.w))
			|| ((posAndSize.y + posAndSize.w)> posAndSizeNearX.y && (posAndSize.y + posAndSize.w) < (posAndSizeNearX.y + posAndSizeNearX.w))){
			return true;
		}
	}
	return false;
}

void Physics2D::collide(ObjectPhysics2D* objectA, std::vector<Veng::ObjectPhysics2D* > collisionGroup){
	objectA->undoMovement();
	for (auto& collisionObject : collisionGroup){ // undo this cycles movement as it caused an intersection
		collisionObject->undoMovement();
		int runCounter(0);
		int runMax(10);
		while (true){ // no longer easy determistic run time
			runCounter++;
			if (twoObjectIntersection(objectA, collisionObject)){
				collisionObject->suckToCenter();
				objectA->pushOut();
			}
			else{
				break;
			}
			if (runCounter == runMax){
				objectA->setPosition(glm::vec2(objectA->getPosition().x + collisionObject->getPosAndBoundary().w, objectA->getPosition().y - collisionObject->getPosAndBoundary().z)); // allthogh working this is not recommended
				break;
			}
		}
	}

	if (collisionGroup.size() > 1){
		glm::vec2 objectAMomentum(glm::vec2(objectA->getMomentum().x / collisionGroup.size(), objectA->getMomentum().y / collisionGroup.size()));
		objectA->setSpeed(((2.0f * (objectA->getMomentum() + collisionGroup[0]->getMomentum())) / (objectA->getMass() + collisionGroup[0]->getMass())) - objectA->getSpeed());

		for (auto& collisionObject : collisionGroup){
			collisionObject->setSpeed(((2.0f * (objectAMomentum + collisionObject->getMomentum())) / (objectA->getMass() + collisionObject->getMass())) - collisionObject->getSpeed());
			collisionObject->lock(); // every object in a collision can only collide once per cycle
		}
	}
	else{
		glm::vec2 objectAMomentum(objectA->getMomentum());
		objectA->setSpeed(((2.0f * (objectA->getMomentum() + collisionGroup[0]->getMomentum())) / (objectA->getMass() + collisionGroup[0]->getMass())) - objectA->getSpeed());
		collisionGroup[0]->setSpeed(((2.0f * (objectAMomentum + collisionGroup[0]->getMomentum())) / (objectA->getMass() + collisionGroup[0]->getMass())) - collisionGroup[0]->getSpeed());
		collisionGroup[0]->lock();
	}
	objectA->lock();
}
}