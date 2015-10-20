#include "Orientation2D.h"

namespace Veng{

glm::vec4 getAdjustedPosAndSize(glm::vec4 positionAndSize, OrientationFlag orientationFlag){
	glm::vec4 adjustedPosAndSize;

	switch (orientationFlag){
	case OrientationFlag::BOTTOM_LEFT:
		adjustedPosAndSize = positionAndSize;
		break;
	case OrientationFlag::CENTER:
		adjustedPosAndSize = glm::vec4(positionAndSize.x - (positionAndSize.w / 2), positionAndSize.y - (positionAndSize.z / 2), positionAndSize.w, positionAndSize.z);
		break;
	case OrientationFlag::TOP_RIGHT:
		adjustedPosAndSize = glm::vec4(positionAndSize.x - positionAndSize.w, positionAndSize.y - positionAndSize.z, positionAndSize.w, positionAndSize.z);
		break;
	}

	return adjustedPosAndSize;
}

}