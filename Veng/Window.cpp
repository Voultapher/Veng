#include "Window.h"
#include "Errors.h"

namespace Veng{

	Window::Window()
	{
	}


	Window::~Window()
	{
	}

	int Window::create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags){
		_screenWidth = screenWidth;
		_screenHeight = screenHeight;

		Uint32 flags = SDL_WINDOW_OPENGL;

		switch (currentFlags){ // set the window flags

		case INVISIBLE:
			flags |= SDL_WINDOW_HIDDEN;

		case FULLSCREEN:
			flags |= SDL_WINDOW_FULLSCREEN;

		case BORDERLESS:
			flags |= SDL_WINDOW_BORDERLESS;
		}




		_sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags); // create the SDL window
		if (_sdlWindow == nullptr){
			fatalError("SDL window could not be created!");
		}

		SDL_GLContext glContext = SDL_GL_CreateContext(_sdlWindow);
		if (glContext == nullptr){
			fatalError("SDL_GL could not be created");
		}

		GLenum error = glewInit();
		if (error != GLEW_OK){
			fatalError("Could not initialize glew");
		}

		glClearColor(0.02f, 0.07f, 0.09f, 1.0f);

		printf("*** OpenGL Versiojn %s ***", glGetString(GL_VERSION));

		SDL_GL_SetSwapInterval(1); // 0 = V-SYNC off, 1 = V-SYNC on

		return 0; //everything worked
	}

	void Window::swapBuffer(){
		SDL_GL_SwapWindow(_sdlWindow);
	}

}