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
#include <Veng/PhysicsManager.h>
#include <Veng/ObjectPhysics2D.h>
#include <Veng/Timing.h>
#include <Veng/RandomEngine.h>

#include <functional>

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
	void drawGraphics();
	void calculateFPS();

	template<typename T>
	void moveObject(T* physicsObject, glm::vec2 direction);

	template<typename T>
	void deleteObject(std::vector<T*>& objectVec, int vecPosition);

	World _world;

	Player _player1;

	bool _bulletSpawnable;
	std::vector<Bullet*> _bullets;
	void spawnBullet();

	Veng::Window _window;
	int _screenWidth;
	int _screenHeight;
	GameState _gameState;

	Veng::GLSLProgram _colorProgram;
	Veng::Camera2D _camera;
	Veng::SpriteBatch _spriteBatch;
	Veng::InputManager _inputManager;
	Veng::FpsLimiter _fpsLimiter;
	Veng::PhysicsManager _physicsManager;
	Veng::RandomEngine _random;

	float _maxFPS;
	float _fps;

	float _time;
	Veng::Vsync _vsyncFlag;
	unsigned int _windowFlags;

	glm::vec4 _normUV;
	Veng::Color _colorWhite;
};

