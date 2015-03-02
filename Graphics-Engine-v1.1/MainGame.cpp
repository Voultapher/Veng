#include <iostream>
#include <string>
#include <cstdlib>

#include "MainGame.h"
#include "Errors.h"

MainGame::MainGame() : 
	_window(nullptr),
	_screenWidth(1280),
	_screenHeight(720),
	_gameState(GameState::PLAY),
	_maxFPS(60.0f),
	_time(0)
{

}


MainGame::~MainGame()
{
}

void MainGame::run(){
	initSystems();  // init SDL and GLSL

	int numSprites = 2;
	for (int i = 0; i < numSprites; i++){ // create sprites
		_sprites.push_back(new Sprite());
		float posSprite = (float)(i+1) / (float)numSprites;
		_sprites.back()->init(posSprite-1.0f, posSprite-1.0f, posSprite, posSprite, "Textures/Player/p1_front.png");
	}

	gameLoop(); // run the game loop
}

void MainGame::initSystems(){
	//Initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	_window = SDL_CreateWindow("Graphics Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);
	if (_window == nullptr){
		fatalError("SDL window could not be created!");
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(_window);
	if (glContext == nullptr){
		fatalError("SDL_GL could not be created");
	}

	GLenum error = glewInit();
	if (error != GLEW_OK){
		fatalError("Could not initialize glew");
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glClearColor(0.02f, 0.07f, 0.09f, 1.0f);

	printf("*** OpenGL Versiojn %s ***", glGetString(GL_VERSION));

	SDL_GL_SetSwapInterval(1); // 0 = V-SYNC off, 1 = V-SYNC on

	initShaders();
}

void MainGame::initShaders(){
	_colorProgram.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexColor");
	_colorProgram.addAttribute("vertexUV");
	_colorProgram.linkShaders();
}

void MainGame::gameLoop(){
	while (_gameState != GameState::EXIT){ // check for game states

		// float startTicks = SDL_GetTicks(); // used for frame time measuring
		processInput();
		drawGraphics();
		_time += 0.05;
		calculateFPS();

		static int frameCounter = 0;
		frameCounter++;
		if (frameCounter == 10){
			printf("%.2f\n", _fps); // print only once every 10 frames
			frameCounter = 0;
		}

		/* float frameTicks = (SDL_GetTicks()) - startTicks; // this is commented out as I have turned on V-SYNC
		if (1000.0f / _maxFPS > frameTicks){
			SDL_Delay(1000.0f / (_maxFPS - frameTicks));
		} */
	}
}

void MainGame::processInput(){
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)){
		switch (evnt.type){
		case SDL_QUIT:
			_gameState = GameState::EXIT; 
			break;
		case SDL_MOUSEMOTION:
			//std::cout << evnt.motion.x << " " << evnt.motion.y << "\n";
			break;
		}
	}
}

void MainGame::drawGraphics(){

	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_colorProgram.use();
	glActiveTexture(GL_TEXTURE0);
	GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
	glUniform1f(textureLocation, 0); // ben says 1i but I think thats false

	GLint timeLocation = _colorProgram.getUniformLocation("time");
	glUniform1f(timeLocation, _time);

	int spritesSize = _sprites.size();
	for (int i = 0; i < spritesSize; i++){
		_sprites[i]->draw();
	}
	glBindTexture(GL_TEXTURE_2D, 0);

	_colorProgram.unUse();

	SDL_GL_SwapWindow(_window);
}

void MainGame::calculateFPS(){
	static const int NUM_SAMPLES = 10;
	static float frameTimes[NUM_SAMPLES];
	static int currentFrame = 0;

	static float prevTicks = SDL_GetTicks();

	float currentTicks;
	currentTicks = SDL_GetTicks();

	_frameTime = currentTicks - prevTicks;
	frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;

	int count;
	currentFrame++;

	if (currentFrame < NUM_SAMPLES){
		count = currentFrame;
	}
	else{
		count = NUM_SAMPLES;
	}

	float frameTimeAverage = 0;
	for (int i = 0; i < count; i++){
		frameTimeAverage += frameTimes[i];
	}
	frameTimeAverage /= count;

	if (frameTimeAverage > 0){
		_fps = 1000.0f / frameTimeAverage;
	}
	else{
		_fps = -666.0f; // the evil fps
	}

	prevTicks = currentTicks;

}