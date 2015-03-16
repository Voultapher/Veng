#include "Physics2D.h"

#include <cstdlib>

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
	int physicsObjectsSize = _physicsObjects.size();

	for (int i = 0; i < physicsObjectsSize; i++){
		if (physicsObject == _physicsObjects[i]){
			_physicsObjects[i] = _physicsObjects.back();
			_physicsObjects.pop_back();
			physicsObjectsSize--;
		}
	}
}

void Physics2D::update(){

	int physicsObjectsSize = _physicsObjects.size();

}

ObjectPhysics2D* Physics2D::findIntersection(ObjectPhysics2D* physicsObject){ // naive implementation O(n^2)
	glm::vec4 posAndSize = physicsObject->getPosAndBoundary();

	int physicsObjectsSize = _physicsObjects.size();

	for (int i = 0; i < physicsObjectsSize; i++){
		glm::vec4 posAndSizeNearX = _physicsObjects[i]->getPosAndBoundary();
		if ( (posAndSize.x > posAndSizeNearX.x && (posAndSize.x < (posAndSizeNearX.x + posAndSizeNearX.z)))
			|| ((posAndSize.x + posAndSize.z) > posAndSizeNearX.x && ((posAndSize.x + posAndSize.z) < (posAndSizeNearX.x + posAndSizeNearX.z))) ){
			//glm::vec4 posAndSizeNearY = _physicsObjects[i]->getPosAndBoundary();
				if ( (posAndSize.y > posAndSizeNearX.y && posAndSize.y < (posAndSizeNearX.y + posAndSizeNearX.w))
					|| ((posAndSize.y + posAndSize.w)> posAndSizeNearX.y && (posAndSize.y + posAndSize.w) < (posAndSizeNearX.y + posAndSizeNearX.w)) ){
						return _physicsObjects[i];
					}
			}
	}

	return nullptr;
}

/*ObjectPhysics2D* Physics2D::findIntersection(ObjectPhysics2D* physicsObject){
	bool xFit = false;
	bool yFit = false;
	bool sameObject = false;
	glm::vec4 posAndSize = physicsObject->getPosAndSize();

	auto mitX = _posX.lower_bound(posAndSize.x);

	if (mitX == _posX.end()){
		return nullptr;
	}
	
	glm::vec4 posAndSizeNearX = mitX->second->getPosAndSize();
	if (posAndSize.x > posAndSizeNearX.x && (posAndSize.x < (posAndSizeNearX.x + posAndSizeNearX.z))){
		xFit = true;

		auto mitY = _posY.lower_bound(posAndSize.y);

		if (mitY == _posY.end()){
			return nullptr; // nsir
		}

		glm::vec4 posAndSizeNearY = mitY->second->getPosAndSize();
		if (posAndSize.y > posAndSizeNearY.y && posAndSize.y < (posAndSizeNearY.y + posAndSizeNearY.w)){
			yFit = true;

			if (mitX == mitY){
				sameObject = true;
			}
		}
	}

	if (xFit && yFit){ // set of conditions for positive collision
		if (sameObject){
			return mitX->second;
		}
	}

	return nullptr;

}*/

void Physics2D::collide(ObjectPhysics2D* objectA, ObjectPhysics2D* objectB){
	// calculate impuls mass * speed and add those vec wise


	glm::vec2 newMomentumA = objectB->getMomentum() - objectA->getMomentum();
	glm::vec2 newMomentumB = objectA->getMomentum() - objectB->getMomentum();

	collideA(objectA, objectB, newMomentumA);
	collideA(objectB, objectA, newMomentumB);
	
}

void Physics2D::collideA(ObjectPhysics2D* objectA, ObjectPhysics2D* objectB, glm::vec2 newMomentum){
	glm::vec2 newDirectionA;
	glm::vec2 newDirectionB;

	if (objectA->getSpeed() != 0.0f && objectB->getSpeed() != 0.0f){

		newDirectionA = glm::normalize(newMomentum / (objectA->getSpeed() * objectA->getMass()));

		objectA->setDirection(newDirectionA);

		objectA->move(newDirectionA);
	}

	else{
		if (objectA->getSpeed() != 0.0f){
			newDirectionA = -objectA->getDirection();
			objectA->setDirection(newDirectionA);
			objectA->move(newDirectionA);
		}
		else{
			float newSpeedA = objectB->getSpeed() * (objectB->getMass() / objectA->getMass());
			objectA->setSpeed(newSpeedA);
			objectA->move(-objectB->getDirection());
			objectA->setSpeed(0.0f);
		}
	}
}

}