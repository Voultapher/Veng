#include "Alignment2D.h"

namespace veng{

glm::vec4 getAdjustedPosAndSize(const glm::vec4 positionAndSize, const Alignment2D alignment2D){
	glm::vec4 adjustedPosAndSize;

	switch (alignment2D){
	case Alignment2D::BOTTOM_LEFT:
		adjustedPosAndSize = positionAndSize;
		break;
	case Alignment2D::CENTER:
		adjustedPosAndSize = glm::vec4(positionAndSize.x - (positionAndSize.w / 2), positionAndSize.y - (positionAndSize.z / 2), positionAndSize.w, positionAndSize.z);
		break;
	case Alignment2D::TOP_RIGHT:
		adjustedPosAndSize = glm::vec4(positionAndSize.x - positionAndSize.w, positionAndSize.y - positionAndSize.z, positionAndSize.w, positionAndSize.z);
		break;
	}

	return adjustedPosAndSize;
}

}