#pragma once

#include <glm/glm.hpp>

#include "Alignment2D.h"
#include "GLTexture.h"

namespace veng{

	struct InitPackage2D{

		GLTexture texture;

		glm::vec4 posAndSize;
		float mass;
		glm::vec2 speed;
		float boundaryScale;
		float friction;
		bool stationanry = false; // make sure not to spawn a staionary object inside another object
		Alignment2D alignment2D = Alignment2D::BOTTOM_LEFT;

		glm::vec4 createPosAndBoundary(){
			glm::vec4 posAndBoundary(posAndSize.x, posAndSize.y, posAndSize.z * boundaryScale, posAndSize.w * boundaryScale);
			return getAdjustedPosAndSize(posAndBoundary, alignment2D);
		}
	};

}