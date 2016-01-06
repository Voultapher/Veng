#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>

#include <string>

namespace veng{

	namespace WindowFlag{ enum WindowFlags { INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4, RESIZABLE = 0x8 }; }

	enum class Vsync { VSYNC_ON, VSYNC_OFF };

	class Window
	{
	public:
		Window();
		~Window();

		void create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags, Vsync vsyncMode);

		void swapBuffer();

		int getScreenWidth() const { _screenWidth; }
		int getScreenHeight() const { _screenHeight; }

	private:
		SDL_Window* _sdlWindow;
		int _screenWidth, _screenHeight;
	};

}