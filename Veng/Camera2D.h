#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Zone2D.h"

namespace veng{

	class Camera2D
	{
	public:
		Camera2D();
		~Camera2D();

		void init(int screenWidth, int screenHeight);
		void update();

		bool isVisible(ObjectPhysics2D* object);

		// setters
		void setPosition(const glm::vec2& newPosition) { _position = newPosition; _needsMatrixUpdate = true; }
		void setScale(float newScale) { _scale = newScale; _needsMatrixUpdate = true; }

		//getters
		float getScale() { return _scale; }
		glm::vec2 getPosition() { return _position; }
		glm::mat4 getCameraMatrix() { return _cameraMatrix; }
		glm::vec2 convertScreenToWorld(glm::vec2 screenCoords);
	private:

		bool _needsMatrixUpdate;
		int _screenWidth, _screenHeight;
		Zone2D _cameraZone;
		float _scale;
		glm::vec2 _position;
		glm::mat4 _cameraMatrix;
		glm::mat4 _orthoMatrix;
	};

}