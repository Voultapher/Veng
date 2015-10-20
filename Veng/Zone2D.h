#pragma once

#include <glm\glm.hpp>

#include "ObjectPhysics2D.h"
#include "Orientation2D.h"

namespace Veng{

class Zone2D
{
public:
	Zone2D();
	~Zone2D();

	void init(glm::vec4 positionAndSize, OrientationFlag orientationFlag);

	bool isInside(ObjectPhysics2D* objectPhysics);
	bool isOutside(ObjectPhysics2D* objectPhysics);

	glm::vec2 getPosition() const { return glm::vec2(_positionAndSize.x, _positionAndSize.y); }
	glm::vec2 getSize() const { return glm::vec2(_positionAndSize.w, _positionAndSize.z); }
	glm::vec4 getPositionAndSize() const { return _positionAndSize; }

private:
	glm::vec4 _positionAndSize;

};

}