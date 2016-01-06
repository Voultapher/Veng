#include <SDL/SDL.h>
#include <GL/glew.h>

#include "veng.h"

namespace veng{

	int init(){
		SDL_Init(SDL_INIT_EVERYTHING); // Initialize SDL
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // this enables double buffering, so that the window wont flicker

		return 0;
	}

}