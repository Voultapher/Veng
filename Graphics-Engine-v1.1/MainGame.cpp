#include <iostream>
#include <string>
#include <cstdlib>

#include "MainGame.h"
#include <Veng/Errors.h>
#include <Veng/ResourceManager.h>

MainGame::MainGame() : 
	_screenWidth(1280),
	_screenHeight(720),
	_gameState(GameState::PLAY),
	_maxFPS(90.0f),
	_time(0),
	_vsyncFlag(Veng::VSYNC_ON),
	_windowFlags(Veng::BORDERLESS)
{

}


MainGame::~MainGame()
{
}

void MainGame::run(){
	initSystems();  // init SDL and GLSL

	gameLoop(); // run the game loop
}

void MainGame::initSystems(){

	Veng::init();

	_window.create("Graphics-Engine", _screenWidth, _screenHeight, _windowFlags, _vsyncFlag);
	_camera.init(_screenWidth, _screenHeight);

	initShaders();
	_spriteBatch.init();
	_fpsLimiter.init(_maxFPS);
}

void MainGame::initShaders(){
	_colorProgram.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexColor");
	_colorProgram.addAttribute("vertexUV");
	_colorProgram.linkShaders();
}

void MainGame::gameLoop(){
	static int frameCounter = 0;

	while (_gameState != GameState::EXIT){ // check for game states

		_fpsLimiter.begin();

		processInput();
		_time += 0.05;

		_camera.update();

		drawGraphics();

		_fps = _fpsLimiter.end();

		frameCounter++;
		if (frameCounter == 10){
			printf("%.2f\n", _fps); // print fps only every 10 frames
			frameCounter = 0;
		}
	}
}

void MainGame::processInput(){
	SDL_Event evnt;

	const float CAMERA_SPEED = 5.0f;
	const float SCALE_SPEED = 0.02f;

	while (SDL_PollEvent(&evnt)){
		switch (evnt.type){
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			//std::cout << evnt.motion.x << " " << evnt.motion.y << "\n";
			break;
		case SDL_KEYDOWN:
			_inputManager.keyDown(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			_inputManager.keyUp(evnt.key.keysym.sym);
			break;
		}
	}

	if (_inputManager.isKeyPressed(SDLK_w)){
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, CAMERA_SPEED));
	}

	if (_inputManager.isKeyPressed(SDLK_s)){
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, -CAMERA_SPEED));
	}

	if (_inputManager.isKeyPressed(SDLK_a)){
		_camera.setPosition(_camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0f));
	}

	if (_inputManager.isKeyPressed(SDLK_d)){
		_camera.setPosition(_camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0f));
	}

	if (_inputManager.isKeyPressed(SDLK_q)){
		_camera.setScale(_camera.getScale() + SCALE_SPEED);
	}

	if (_inputManager.isKeyPressed(SDLK_e)){
		_camera.setScale(_camera.getScale() - SCALE_SPEED);
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
	glUniform1f(timeLocation, _time); //set time variable

	GLint pLocation = _colorProgram.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0])); // upload camera Information to the GPU

	_spriteBatch.begin();
	glm::vec4 pos(0.0f, 0.0f, 50.0f, 50.0f);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static Veng::GLTexture texture = Veng::ResourceManager::getTexture("Textures/Player/p1_hurt.png");
	Veng::Color color;
	color.setColor(220, 218, 148, 255);

	for (int i = 0; i < 1000; i++){
		_spriteBatch.draw(pos + glm::vec4((float)i*60 + sin(i)*10, sin(_time) * 100, 0.0f, 0.0f), uv, texture.id, 0.0f, color);
	}

	_spriteBatch.end();

	_spriteBatch.renderBatches();

	glBindTexture(GL_TEXTURE_2D, 0);

	_colorProgram.unUse();

	_window.swapBuffer();
}