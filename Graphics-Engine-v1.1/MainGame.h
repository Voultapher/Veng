#pragma once

#include <vector>
#include <map>
#include <string>

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
#include <Veng/PhysicsManager.h>
#include <Veng/ObjectPhysics2D.h>
#include <Veng/Timing.h>
#include <Veng/RandomEngine.h>
#include <Veng/Schedule.h>

#include <functional>

#include "GameObjects.h"
#include "Bullet.h"
#include "Player.h"
#include "World.h"

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
	void playerMovement();
	void camaraMovement();
	void drawGraphics();
	void updateGameObjects();
	Veng::Color speedColor(float speed, float max);

	World _world;

	GameObjects _gameObjects;
	Veng::Schedule _player1Schedule;

	void spawnBullet(glm::vec2 position, glm::vec2 force);
	Veng::Schedule _bulletSchedule;
	void madness();
	void sprinkle();
	void revert();
	void still();
	Veng::Schedule _sprinkleSchedule;

	float _friction;

	Veng::Window _window;
	int _screenWidth;
	int _screenHeight;
	GameState _gameState;

	Veng::GLSLProgram _colorProgram;
	Veng::Camera2D _camera;
	Veng::SpriteBatch _spriteBatch;
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

	glm::vec4 _normUV;
	Veng::Color _colorWhite;
};

