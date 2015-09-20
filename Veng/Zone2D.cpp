#include "Zone2D.h"

namespace Veng{

Zone2D::Zone2D()
{
}


Zone2D::~Zone2D()
{
}

void Zone2D::init(glm::vec4 positionAndSize, OrientationFlag orientationFlag){

	switch (orientationFlag){
	case OrientationFlag::BOTTOM_LEFT:
		_positionAndSize = positionAndSize;
		break;
	case OrientationFlag::CENTER:
		_positionAndSize = glm::vec4(positionAndSize.x - (positionAndSize.w / 2), positionAndSize.y - (positionAndSize.z / 2), positionAndSize.w, positionAndSize.z);
		break;
	case OrientationFlag::TOP_RIGHT:
		_positionAndSize = glm::vec4(positionAndSize.x - positionAndSize.w, positionAndSize.y - positionAndSize.z, positionAndSize.w, positionAndSize.z);
		break;
	}
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

}