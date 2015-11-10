#include "InputManager.h"


namespace Veng{

InputManager::InputManager() :
_mousePosition(0.0f)
{
}


InputManager::~InputManager()
{
}

void InputManager::keyDown(unsigned int keyID){
	_keyMap[keyID] = true;
	_activeKeyMap[keyID] = false;
}

void InputManager::keyUp(unsigned int keyID){
	_keyMap[keyID] = false;
}

void InputManager::setMousePosition(float x, float y){
	_mousePosition.x = x;
	_mousePosition.y = y;
}

bool InputManager::isKeyDown(unsigned int keyID){
	auto it = _keyMap.find(keyID);
	if (it != _keyMap.end()){
		return it->second;
	}
	
	return false;
}

bool InputManager::isKeyNewPress(unsigned int keyID){
	auto it = _keyMap.find(keyID);
	if (it != _keyMap.end()){
		auto active = _activeKeyMap.find(keyID);
		if (active != _activeKeyMap.end()){
			if (active->second == false){
				active->second = true;
				return true;
			}
		}
	}

	return false;
}

}