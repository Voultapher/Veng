#pragma once

#include <glm/glm.hpp>

namespace Veng{

	struct PhysicsInitPackage2D{

		glm::vec4 posAndSize;
		float mass;
		glm::vec2 speed;
		float boundaryScale;
		float friction;
		bool stationanry = false; // make sure not to spawn a staionary object inside another object
	};

}