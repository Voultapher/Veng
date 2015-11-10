#pragma once

#include <vector>
#include <map>
#include <string>
#include <functional>

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include <Veng/Veng.h>
#include <Veng/Window.h>
#include <Veng/Render.h>
#include <Veng/InputManager.h>
#include <Veng/PhysicsManager.h>
#include <Veng/ObjectPhysics2D.h>
#include <Veng/Timing.h>
#include <Veng/RandomEngine.h>
#include <Veng/Schedule.h>
#include <Veng/Zone2D.h>

#include "GameObjects.h"
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
	void gameLoop();
	void processInput();
	void playerMovement();
	void camaraMovement();
	void updateGameObjects();

	Veng::Zone2D _worldBorder;

	GameObjects _gameObjects;
	Veng::Schedule _player1Schedule;

	void spawnBullet(glm::vec2 position, glm::vec2 force);
	Veng::Schedule _bulletSchedule;
	void madness();
	void sprinkle();
	void revert();
	void still();
	Veng::Schedule _sprinkleSchedule;


	int _screenWidth;
	int _screenHeight;
	unsigned int _maxObjects;
	GameState _gameState;

	Veng::Render _render;
	Veng::InputManager _inputManager;
	Veng::FpsLimiter _fpsLimiter;
	Veng::Schedule _fpsSchedule;
	Veng::PhysicsManager _physicsManager;
	Veng::RandomEngine _random;

	float _maxFPS;
	float _fps;
	float _frameTime;
	float _frameTicks;

	float _time;
	Veng::Vsync _vsyncFlag;
	unsigned int _windowFlags;
};

