#pragma once

#include <unordered_map>

namespace Veng{

class InputManager
{
public:
	InputManager();
	~InputManager();


	void keyDown(unsigned int keyID);
	void keyUp(unsigned int keyID);

	bool isKeyPressed(unsigned int keyID);

private:
	std::unordered_map<unsigned int, bool> _keyMap;
};

}