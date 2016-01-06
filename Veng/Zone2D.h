#pragma once

#include <glm\glm.hpp>

#include "ObjectPhysics2D.h"
#include "Alignment2D.h"

namespace veng{

class Zone2D
{
public:
	Zone2D();
	~Zone2D();

	void init(const glm::vec4 positionAndSize, const Alignment2D alignment2D);
	void updatePosition(const glm::vec2& newPosition);
	void updatePosAndSize(const glm::vec4& newPosAndSize);

	bool isInside(ObjectPhysics2D* objectPhysics);
	bool isOutside(ObjectPhysics2D* objectPhysics);

	bool isInsideVisual(ObjectPhysics2D* objectPhysics);
	bool isOutsideVisual(ObjectPhysics2D* objectPhysics);

	glm::vec2 getPosition() const { return glm::vec2(_positionAndSize.x, _positionAndSize.y); }
	glm::vec2 getSize() const { return glm::vec2(_positionAndSize.w, _positionAndSize.z); }
	glm::vec4 getPositionAndSize() const { return _positionAndSize; }

private:
	Alignment2D _alignment2D;
	glm::vec4 _positionAndSize;

};

}