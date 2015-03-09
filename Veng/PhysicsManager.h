#pragma once

#include <vector>

namespace Veng{

template<typename T>
class PhysicsManager
{
public:
	PhysicsManager();
	~PhysicsManager();

	void addPhysicsObject(T* physicsObject);

private:
	std::vector<T*> _physicsObjects;
};

}