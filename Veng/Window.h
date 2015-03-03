#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>

#include <string>

namespace Veng{

	enum WindowFlags { INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4 };

	enum Vsync { VSYNC_ON = 0x1, VSYNC_OFF = 0x2 };

	class Window
	{
	public:
		Window();
		~Window();

		int create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags, unsigned char vsyncFlag);

		void swapBuffer();

		int getScreenWidth() { _screenWidth; }
		int getScreenHeight() { _screenHeight; }

	private:
		SDL_Window* _sdlWindow;
		int _screenWidth, _screenHeight;
	};

}