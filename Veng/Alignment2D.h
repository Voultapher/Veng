#pragma once

#include <glm\glm.hpp>

namespace veng{

	enum class Alignment2D { BOTTOM_LEFT, CENTER, TOP_RIGHT }; // determines how the boudary is set

extern glm::vec4 getAdjustedPosAndSize(const glm::vec4 positionAndSize, const Alignment2D alignment2D);

}