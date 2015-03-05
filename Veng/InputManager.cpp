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
}

void InputManager::keyUp(unsigned int keyID){
	_keyMap[keyID] = false;
}

void InputManager::setMousePosition(float x, float y){
	_mousePosition.x = x;
	_mousePosition.y = y;
}

bool InputManager::isKeyPressed(unsigned int keyID){
	auto it = _keyMap.find(keyID);
	if (it != _keyMap.end()){
		return it->second;
	}
	else{
		return false;
	}
}

}