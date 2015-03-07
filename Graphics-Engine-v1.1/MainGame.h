#pragma once

#include <vector>

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include <Veng/Veng.h>
#include <Veng/GLSLProgram.h>
#include <Veng/Sprite.h>
#include <Veng/Window.h>
#include <Veng/Camera2D.h>
#include <Veng/SpriteBatch.h>
#include <Veng/InputManager.h>
#include <Veng/Timing.h>

#include <vector>

#include "Bullet.h"
#include "Player.h"

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

	Player _player1;

	std::vector<Bullet> _bullets;

	Veng::Window _window;
	int _screenWidth;
	int _screenHeight;
	GameState _gameState;

	Veng::GLSLProgram _colorProgram;
	Veng::Camera2D _camera;
	Veng::SpriteBatch _spriteBatch;
	Veng::InputManager _inputManager;
	Veng::FpsLimiter _fpsLimiter;

	float _maxFPS;
	float _fps;

	float _time;
	Veng::Vsync _vsyncFlag;
	unsigned int _windowFlags;

	glm::vec4 _normUV;
	Veng::Color _colorWhite;
};

