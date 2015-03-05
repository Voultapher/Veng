#pragma once

#include <unordered_map>
#include <glm/glm.hpp>

namespace Veng{

class InputManager
{
public:
	InputManager();
	~InputManager();


	void keyDown(unsigned int keyID);
	void keyUp(unsigned int keyID);

	void setMousePosition(float x, float y);
	glm::vec2 getMousePosition() const { return _mousePosition; }

	bool isKeyPressed(unsigned int keyID);

private:
	std::unordered_map<unsigned int, bool> _keyMap;
	glm::vec2 _mousePosition;
};

}