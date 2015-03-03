#pragma once

#include <vector>

#include <SDL/SDL.h>
#include <GL/glew.h>

#include <Veng/Veng.h>
#include <Veng/GLSLProgram.h>
#include <Veng/Sprite.h>
#include <Veng/Window.h>
#include <Veng/Camera2D.h>
#include <Veng/SpriteBatch.h>

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

	Veng::Window _window;
	int _screenWidth;
	int _screenHeight;
	GameState _gameState;

	Veng::GLSLProgram _colorProgram;
	Veng::Camera2D _camera;
	Veng::SpriteBatch _spriteBatch;

	float _fps;
	float _maxFPS;
	float _frameTime;

	float _time;
};

