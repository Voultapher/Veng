#include "Window.h"
#include "Errors.h"

namespace veng{

Window::Window()
{
}


Window::~Window()
{
}

void Window::create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentsdlFlags, Vsync vsyncMode){
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;

	Uint32 sdlFlags = SDL_WINDOW_OPENGL;

	if (currentsdlFlags & WindowFlag::INVISIBLE){
		sdlFlags |= SDL_WINDOW_HIDDEN;
	}
	if (currentsdlFlags & WindowFlag::FULLSCREEN){
		sdlFlags |= SDL_WINDOW_FULLSCREEN;
	}
	if (currentsdlFlags & WindowFlag::BORDERLESS){
		sdlFlags |= SDL_WINDOW_BORDERLESS;
	}
	if (currentsdlFlags & WindowFlag::RESIZABLE){
		sdlFlags |= SDL_WINDOW_RESIZABLE;
	}

	_sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, sdlFlags); // create the SDL window
	if (_sdlWindow == nullptr){
		fatalError("SDL window could not be created!");
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(_sdlWindow);
	if (glContext == nullptr){
		fatalError("SDL_GL_CreateContext could not be created");
	}

	GLenum error = glewInit();
	if (error != GLEW_OK){
		fatalError("Could not initialize glew");
	}

	glClearColor(0.02f, 0.07f, 0.09f, 1.0f); // BackgroundColor

	printf("*** OpenGL Versiojn %s ***", glGetString(GL_VERSION));

	if (vsyncMode == Vsync::VSYNC_ON){ // set Vsync on or off
		SDL_GL_SetSwapInterval(1);
	}
	else if (vsyncMode == Vsync::VSYNC_OFF){
		SDL_GL_SetSwapInterval(0);
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Window::swapBuffer(){
	SDL_GL_SwapWindow(_sdlWindow);
}

}