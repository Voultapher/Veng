#pragma once

#include <vector>
#include <map>
#include <string>
#include <functional>

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include <veng/veng.h>
#include <veng/Window.h>
#include <veng/Render.h>
#include <veng/InputManager.h>
#include <veng/PhysicsManager.h>
#include <veng/ObjectPhysics2D.h>
#include <veng/Timing.h>
#include <veng/RandomEngine.h>
#include <veng/Schedule.h>
#include <veng/Zone2D.h>

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

	veng::Zone2D _worldBorder;

	GameObjects _gameObjects;
	veng::Schedule _player1Schedule;

	void spawnBullet(glm::vec2 position, glm::vec2 force);
	veng::Schedule _bulletSchedule;
	void madness();
	void sprinkle();
	void revert();
	void still();
	veng::Schedule _sprinkleSchedule;


	int _screenWidth;
	int _screenHeight;
	std::size_t _maxObjects;
	GameState _gameState;

	veng::Render _render;
	veng::InputManager _inputManager;
	veng::FpsLimiter _fpsLimiter;
	veng::Schedule _fpsSchedule;
	veng::PhysicsManager _physicsManager;
	veng::RandomEngine _random;

	float _maxFPS;
	float _fps;
	float _frameTime;
	float _frameTicks;

	float _time;
	veng::Vsync _vsyncMode;
	unsigned int _windowFlags;
};

