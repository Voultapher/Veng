#pragma once

#include <vector>

#include <SDL/SDL.h>
#include <GL/glew.h>

#include "GLSLProgram.h"
#include "Sprite.h"
#include "GLTexture.h"

enum class GameState{PLAY, EXIT};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

private:
	void initSystems();
	void initShaders();
	void gameLoop();
	void processInput();
	void drawGraphics();
	void calculateFPS();

	SDL_Window* _window;
	int _screenWidth;
	int _screenHeight;
	GameState _gameState;

	std::vector<Sprite *> _sprites;

	GLSLProgram _colorProgram;

	float _fps;
	float _maxFPS;
	float _frameTime;

	float _time;
};

