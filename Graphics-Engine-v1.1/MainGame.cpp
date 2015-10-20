#include <iostream>
#include <string>
#include <cstdlib>

#include "MainGame.h"
#include <Veng/Errors.h>
#include <Veng/ResourceManager.h>
#include <Veng/InitPackage2D.h>

MainGame::MainGame() :
	_friction(0.94f),
	_screenWidth(720),
	_screenHeight(720),
	_maxObjects(1e4),
	_gameState(GameState::PLAY),
	_maxFPS(60.0f),
	_time(0),
	_vsyncFlag(Veng::VSYNC_OFF),
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

	_render.init("Graphics-Engine", _screenWidth, _screenHeight, _windowFlags, _vsyncFlag);
	_physicsManager.init(_maxObjects, _render); // linking the 2 together

	_fpsLimiter.init(_maxFPS);

	_gameObjects.players.emplace_back(new Player);

	const glm::vec2 PLAYER_SPAWN(0.0f, 0.0f); // player init
	const float PLAYER_SPEED = 1.0f;
	Veng::InitPackage2D player1InitPackage;
	player1InitPackage.texture = Veng::ResourceManager::getTexture("Textures/Player/p1_hurt.png");
	player1InitPackage.posAndSize = glm::vec4(PLAYER_SPAWN.x, PLAYER_SPAWN.y, 69.0f, 92.0f);
	player1InitPackage.boundaryScale = 0.8f;
	player1InitPackage.speed = glm::vec2(0.0f);
	player1InitPackage.mass = 6348.0f;
	player1InitPackage.friction = _friction;
	_gameObjects.players[0]->init(100.0f, 1.1f, _physicsManager.addPhysicsObject(player1InitPackage));

	_worldBorder.init(glm::vec4(0.0f, 0.0f, 90000.0f, 90000.0f), Veng::OrientationFlag::CENTER);

	_bulletSchedule.init(100);
	_fpsSchedule.init(500);
	_player1Schedule.init(100);
	_sprinkleSchedule.init(400);

	for (int i = 0; i < 1; i++){ // stress testing game object design
		spawnBullet(glm::vec2(i*25,200), glm::vec2(200.0f));
	}
}

void MainGame::gameLoop(){
	while (_gameState != GameState::EXIT){ // check for game states
		_fpsLimiter.begin(); // mesure frame timee

		processInput();

		updateGameObjects();

		_physicsManager.update();
		_render.update();

		_fps = _fpsLimiter.end(); // delay further calculations based on the target fps
		if (_fpsSchedule.ready()){
			_frameTicks = _fpsLimiter.getFramTicks();
			printf("FPS: %.2f	FrameTicks: %f\n", _fps, _frameTicks);
			//printf("Debug bool = %d\n", (int)_debug);
		}
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
			_inputManager.setMousePosition(evnt.motion.x, evnt.motion.y);
			break;
		case SDL_KEYDOWN:
			_inputManager.keyDown(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			_inputManager.keyUp(evnt.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			_inputManager.keyDown(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			_inputManager.keyUp(evnt.button.button);
			break;
		}
	}


	if (_inputManager.isKeyPressed(SDLK_ESCAPE)){ // close the game with ESC
		_gameState = GameState::EXIT;
	}

	playerMovement();
	camaraMovement();

	if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT)){ // spawn bullets and or do else
		_gameObjects.players[0]->objectPhysics->setPosition(_render.camera.convertScreenToWorld(_inputManager.getMousePosition()));
		if (_bulletSchedule.ready()){
			//madness();
			//sprinkle();
			//revert();
			//still();
		}
	}
}

void MainGame::playerMovement(){
	bool w = false, s = false, a = false, d = false;
	if (_inputManager.isKeyPressed(SDLK_w)){ // player movement
		w = true;
		_gameObjects.players[0]->objectPhysics->addAcceleration(glm::vec2(0.0f, 1.0f) * _gameObjects.players[0]->getMovementSpeed());
	}

	if (_inputManager.isKeyPressed(SDLK_s)){
		s = true;
		_gameObjects.players[0]->objectPhysics->addAcceleration(glm::vec2(0.0f, -1.0f) * _gameObjects.players[0]->getMovementSpeed());
	}

	if (_inputManager.isKeyPressed(SDLK_a)){
		a = true;
		_gameObjects.players[0]->objectPhysics->addAcceleration(glm::vec2(-1.0f, 0.0f) * _gameObjects.players[0]->getMovementSpeed());
	}

	if (_inputManager.isKeyPressed(SDLK_d)){
		d = true;
		_gameObjects.players[0]->objectPhysics->addAcceleration(glm::vec2(1.0f, 0.0f) * _gameObjects.players[0]->getMovementSpeed());
	}

	if (w || s || a || d){
	}
}

void MainGame::camaraMovement(){
	const float CAMERA_SPEED = 10.0f;
	const float SCALE_SPEED = 1.02f;
	const float MIN_SCALE = 0.1f;

	if (_inputManager.isKeyPressed(SDLK_UP)){ // camera movement
		_render.camera.setPosition(_render.camera.getPosition() + glm::vec2(0.0f, CAMERA_SPEED) / _render.camera.getScale());
	}

	if (_inputManager.isKeyPressed(SDLK_DOWN)){
		_render.camera.setPosition(_render.camera.getPosition() + glm::vec2(0.0f, -CAMERA_SPEED) / _render.camera.getScale());
	}

	if (_inputManager.isKeyPressed(SDLK_LEFT)){
		_render.camera.setPosition(_render.camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0f) / _render.camera.getScale());
	}

	if (_inputManager.isKeyPressed(SDLK_RIGHT)){
		_render.camera.setPosition(_render.camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0f) / _render.camera.getScale());
	}

	if (_inputManager.isKeyPressed(SDLK_q)){ // camera zoom
		_render.camera.setScale(_render.camera.getScale() * SCALE_SPEED);
	}

	if (_inputManager.isKeyPressed(SDLK_e)){
		if (_render.camera.getScale() > MIN_SCALE){
			_render.camera.setScale(_render.camera.getScale() / SCALE_SPEED);
		}
	}
}

void MainGame::updateGameObjects(){

	for (int i = 0; i < _gameObjects.bullets.size(); i++){ //update all bullets game logic
		if (_worldBorder.isOutside(_gameObjects.bullets[i]->objectPhysics)){ // checks if this game object is out of bounds of the game world //tmp to be replaced by a unified gameobject system
			_gameObjects.bullets[i]->objectPhysics->pushBackAndStop();
		}

		/*if (_gameObjects.bullets[i]->update()){
			_physicsManager.deleteObject(_gameObjects.bullets[i]->objectPhysics);
			_gameObjects.bullets[i] = _gameObjects.bullets.back();
			//delete _gameObjects.bullets.back(); // this is a memory leak
			_gameObjects.bullets.pop_back();
		}*/
	}

	if (_worldBorder.isOutside(_gameObjects.players[0]->objectPhysics)){
		_gameObjects.players[0]->objectPhysics->pushBackAndStop();
	}
}

void MainGame::spawnBullet(glm::vec2 position, glm::vec2 force){
	float lifeTime = 2000.0f;
	static Veng::GLTexture bulletTextureId = Veng::ResourceManager::getTexture("Textures/Items/keyred.png");

	glm::vec2 mousePosition = _inputManager.getMousePosition();
	mousePosition = _render.camera.convertScreenToWorld(mousePosition);

	Veng::InitPackage2D bulletInitPackage;
	float bulletSize = 35.0f;//_random.generateRandomFloat(15.0f, 25.0f);
	bulletInitPackage.texture = bulletTextureId;
	bulletInitPackage.mass = bulletSize * bulletSize * 10;
	bulletInitPackage.speed = glm::vec2(0.0f);
	bulletInitPackage.posAndSize = glm::vec4(position.x, position.y, bulletSize, bulletSize); //tmp
	//bulletInitPackage.posAndSize = glm::vec4(0.0f, 0.0f, bulletSize, bulletSize); //tmp
	//bulletInitPackage.posAndSize = glm::vec4(playerPosition.x - bulletSize, playerPosition.y - bulletSize, bulletSize, bulletSize);
	bulletInitPackage.boundaryScale = 0.7;
	bulletInitPackage.friction = 0.97f;// _friction;

	_gameObjects.bullets.emplace_back(new Bullet(lifeTime, _physicsManager.addPhysicsObject(bulletInitPackage)));

	_gameObjects.bullets.back()->objectPhysics->applyForce(force);
}

void MainGame::madness(){
	int bullets = 1000;
	for (int i = 0; i < bullets; i++){
		float x = _random.generateRandomFloat(-_worldBorder.getSize().x, _worldBorder.getSize().y);
		float y = _random.generateRandomFloat(-_worldBorder.getSize().x, _worldBorder.getSize().y);
		glm::vec2 position(x, y);
		glm::vec2 force(0.0f);
		spawnBullet(position, force);
	}
}

void MainGame::sprinkle(){
	if (_sprinkleSchedule.ready()){
		float x = _random.generateRandomFloat(-10000.0f, 10000.0f);
		glm::vec2 position( _render.camera.convertScreenToWorld(_inputManager.getMousePosition()) );
		//glm::vec2 force(x, -80000.0f);
		glm::vec2 force(80000.0f, x);
		//glm::vec2 force(0.0f);
		spawnBullet(position, force);
	}
}

void MainGame::revert(){
	if (_sprinkleSchedule.ready()){
		glm::vec2 mousePosition = _render.camera.convertScreenToWorld(_inputManager.getMousePosition());
		glm::vec2 playerPosition = _gameObjects.players[0]->objectPhysics->getPosition();
		glm::vec2 position(mousePosition);
		glm::vec2 force = (playerPosition - mousePosition) * 500.0f;
		spawnBullet(position, force);
	}
}

void MainGame::still(){
	if (_sprinkleSchedule.ready()){
		glm::vec2 mousePosition = _render.camera.convertScreenToWorld(_inputManager.getMousePosition());
		spawnBullet(mousePosition, glm::vec2(0.0f));
	}
}