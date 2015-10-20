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

void Physics2D::reserveData(unsigned int objectCount){
	_posAndBoundarys.reserve(objectCount);
	_physicsObjects.reserve(objectCount);
	std::size_t debug = sizeof(ObjectPhysics2D);
}


ObjectPhysics2D* Physics2D::addObject(){

	_physicsObjects.emplace_back(); // add the object to the cach friendly presized vector
	return &_physicsObjects.back(); // return the items location for efficient storage in the game object

}

glm::vec4* Physics2D::addPosAndBoundary(glm::vec4 posAndBoundary){
	_posAndBoundarys.push_back(posAndBoundary);
	return &_posAndBoundarys.back();
}

/*void Physics2D::deleteObject(ObjectPhysics2D physicsObject){ // bad O(n)
	for (int i = 0; i < _physicsObjects.size(); i++){
		if (physicsObject == _physicsObjects[i]){
			_physicsObjects[i] = _physicsObjects.back();
			_physicsObjects.pop_back();
		}
	}
}*/

void Physics2D::update(){

	for (auto& physicsObject : _physicsObjects){ // first move every object without considering collision, to achieve move certainty
			physicsObject.move();
	}

	for (auto& physicsObject : _physicsObjects){
		if (physicsObject.isLocked() == false){
			std::vector<Veng::ObjectPhysics2D*> intersectingObjects = findIntersection(physicsObject);
			if (intersectingObjects.size() > 0){
				collide(physicsObject, intersectingObjects);
			}
		}
	}

	for (auto& physicsObject : _physicsObjects){ // unlock every object for the next iteration
		physicsObject.unLock();
	}
}

std::vector<Veng::ObjectPhysics2D*> Physics2D::findIntersection(ObjectPhysics2D& physicsObject){ // naive implementation O(n^2)
	glm::vec4 posA = physicsObject.getPosAndBoundary();
	std::vector<Veng::ObjectPhysics2D* > intersectingObjects;

	int i = 0;
	for (auto& posB : _posAndBoundarys){
		if (posA != posB){ // prevents finding itself
			if ((posA.x > posB.x && (posA.x < (posB.x + posB.z))) || ((posA.x + posA.z) > posB.x && ((posA.x + posA.z) < (posB.x + posB.z)))){
				if ((posA.y > posB.y && posA.y < (posB.y + posB.w)) || ((posA.y + posA.w)> posB.y && (posA.y + posA.w) < (posB.y + posB.w))){
					intersectingObjects.push_back(&_physicsObjects[i]);
				}
			}
		}
		i++; // tmp solution
	}

	return intersectingObjects;
}

bool Physics2D::twoObjectIntersection(ObjectPhysics2D* physicsObjectA, ObjectPhysics2D* physicsObjectB){
	glm::vec4 posA = physicsObjectA->getPosAndBoundary();
	glm::vec4 posB = physicsObjectB->getPosAndBoundary();
	if ((posA.x > posB.x && (posA.x < (posB.x + posB.z)))
		|| ((posA.x + posA.z) > posB.x && ((posA.x + posA.z) < (posB.x + posB.z)))){
		if ((posA.y > posB.y && posA.y < (posB.y + posB.w))
			|| ((posA.y + posA.w)> posB.y && (posA.y + posA.w) < (posB.y + posB.w))){
			return true;
		}
	}
	return false;
}

void Physics2D::collide(ObjectPhysics2D& objectA, std::vector<Veng::ObjectPhysics2D*> collisionGroup){
	objectA.undoMovement();
	for (auto collisionObject : collisionGroup){ // undo this cycles movement as it caused an intersection
		collisionObject->undoMovement();
		int runCounter(0);
		int runMax(10);
		while (true){ // no longer easy determistic run time
			runCounter++;
			if (twoObjectIntersection(&objectA, collisionObject)){
				collisionObject->suckToCenter();
				objectA.pushOut();
			}
			else{
				break;
			}
			if (runCounter == runMax){
				objectA.setPosition(glm::vec2(objectA.getPosition().x + collisionObject->getPosAndBoundary().w, objectA.getPosition().y - collisionObject->getPosAndBoundary().z)); // allthogh working this is not recommended
				break;
			}
		}
	}

	if (collisionGroup.size() > 1){
		glm::vec2 objectAMomentum(glm::vec2(objectA.getMomentum().x / collisionGroup.size(), objectA.getMomentum().y / collisionGroup.size()));
		objectA.setSpeed(((2.0f * (objectA.getMomentum() + collisionGroup[0]->getMomentum())) / (objectA.getMass() + collisionGroup[0]->getMass())) - objectA.getSpeed());

		for (auto collisionObject : collisionGroup){
			collisionObject->setSpeed(((2.0f * (objectAMomentum + collisionObject->getMomentum())) / (objectA.getMass() + collisionObject->getMass())) - collisionObject->getSpeed());
			collisionObject->lock(); // every object in a collision can only collide once per cycle
		}
	}
	else{
		glm::vec2 objectAMomentum(objectA.getMomentum());
		objectA.setSpeed(((2.0f * (objectA.getMomentum() + collisionGroup[0]->getMomentum())) / (objectA.getMass() + collisionGroup[0]->getMass())) - objectA.getSpeed());
		collisionGroup[0]->setSpeed(((2.0f * (objectAMomentum + collisionGroup[0]->getMomentum())) / (objectA.getMass() + collisionGroup[0]->getMass())) - collisionGroup[0]->getSpeed());
		collisionGroup[0]->lock();
	}
	objectA.lock();
}
}