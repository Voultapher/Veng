#pragma once

#include <glm\glm.hpp>

namespace Veng{

enum class OrientationFlag { BOTTOM_LEFT, CENTER, TOP_RIGHT }; // determines how the boudary is set

extern glm::vec4 getAdjustedPosAndSize(glm::vec4 positionAndSize, OrientationFlag orientationFlag);

}