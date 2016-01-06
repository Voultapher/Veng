#include "Zone2D.h"

namespace veng{

Zone2D::Zone2D()
{
}


Zone2D::~Zone2D()
{
}

void Zone2D::init(const glm::vec4 positionAndSize, const Alignment2D alignment2D)
{
	_alignment2D = alignment2D;
	_positionAndSize = getAdjustedPosAndSize(positionAndSize, alignment2D);
}

void Zone2D::updatePosition(const glm::vec2& newPosition)
{
	_positionAndSize.x = newPosition.x;
	_positionAndSize.y = newPosition.y;
}

void Zone2D::updatePosAndSize(const glm::vec4& newPosAndSize)
{
	_positionAndSize = getAdjustedPosAndSize(newPosAndSize, _alignment2D);
}

bool Zone2D::isInside(ObjectPhysics2D* objectPhysics){
	glm::vec4 pSAX = objectPhysics->getPosAndBoundary();
	if ((pSAX.x > _positionAndSize.x && (pSAX.x < (_positionAndSize.x + _positionAndSize.z)))
		|| ((pSAX.x + pSAX.z) > _positionAndSize.x && ((pSAX.x + pSAX.z) < (_positionAndSize.x + _positionAndSize.z)))){
		if ((pSAX.y > _positionAndSize.y && pSAX.y < (_positionAndSize.y + _positionAndSize.w))
			|| ((pSAX.y + pSAX.w)> _positionAndSize.y && (pSAX.y + pSAX.w) < (_positionAndSize.y + _positionAndSize.w))){
			return true;
		}
	}
	return false;
}

bool Zone2D::isOutside(ObjectPhysics2D* objectPhysics){
	return !isInside(objectPhysics);
}

bool Zone2D::isInsideVisual(ObjectPhysics2D* objectPhysics){
	glm::vec4 pSAX = objectPhysics->getPosAndSize();
	if ((pSAX.x > _positionAndSize.x && (pSAX.x < (_positionAndSize.x + _positionAndSize.z)))
		|| ((pSAX.x + pSAX.z) > _positionAndSize.x && ((pSAX.x + pSAX.z) < (_positionAndSize.x + _positionAndSize.z)))){
		if ((pSAX.y > _positionAndSize.y && pSAX.y < (_positionAndSize.y + _positionAndSize.w))
			|| ((pSAX.y + pSAX.w)> _positionAndSize.y && (pSAX.y + pSAX.w) < (_positionAndSize.y + _positionAndSize.w))){
			return true;
		}
	}
	return false;
}

bool Zone2D::isOutsideVisual(ObjectPhysics2D* objectPhysics){
	return !isInsideVisual(objectPhysics);
}

}