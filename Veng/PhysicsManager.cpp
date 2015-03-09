#include "PhysicsManager.h"

namespace Veng{

template<typename T>
PhysicsManager<T>::PhysicsManager()
{
}

template<typename T>
PhysicsManager<T>::~PhysicsManager()
{
}

template<typename T>
void PhysicsManager<T>::addPhysicsObject(T* physicsObject){
	_physicsObjects.push_back(T);
}

}