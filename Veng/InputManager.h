#pragma once

#include <unordered_map>
#include <glm/glm.hpp>

namespace veng{

class InputManager
{
public:
	InputManager();
	~InputManager();


	void keyDown(unsigned int keyID);
	void keyUp(unsigned int keyID);

	void setMousePosition(float x, float y);
	glm::vec2 getMousePosition() const { return _mousePosition; }

	bool isKeyDown(unsigned int keyID); // returns whether a key/button is currently pressed
	bool isKeyNewPress(unsigned int keyID); // return whether a key/button was pressed this frame for the first time

private:
	std::unordered_map<unsigned int, bool> _keyMap;
	std::unordered_map<unsigned int, bool> _activeKeyMap;
	glm::vec2 _mousePosition;
};

}