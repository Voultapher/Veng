#include <iostream>
#include <string>
#include <cstdlib>

#include "MainGame.h"
#include <Veng/Errors.h>
#include <Veng/ResourceManager.h>
#include <Veng/PhysicsInitPackage2D.h>

MainGame::MainGame() :
	_friction(0.94f),
	_screenWidth(720),
	_screenHeight(720),
	_gameState(GameState::PLAY),
	_maxFPS(60.0f),
	_time(0),
	_vsyncFlag(Veng::VSYNC_OFF),
	_windowFlags(Veng::BORDERLESS),
	_normUV(0.0f, 0.0f, 1.0f, 1.0f)
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

	const glm::vec2 PLAYER_SPAWN(0.0f, 0.0f); // player init
	const float PLAYER_SPEED = 1.0f;
	Veng::PhysicsInitPackage2D player1InitPackage;
	player1InitPackage.posAndSize = glm::vec4(PLAYER_SPAWN.x, PLAYER_SPAWN.y, 69.0f, 92.0f);
	player1InitPackage.boundaryScale = 0.8f;
	player1InitPackage.speed = glm::vec2(0.0f);
	player1InitPackage.mass = 6348.0f;
	player1InitPackage.friction = _friction;
	_player1.init(100.0f, 0.8f);
	_physicsManager.addPhysicsObject(_player1.objectPhysics, player1InitPackage);

	_colorWhite.setColor(255, 255, 255, 255);

	const float WORLD_SIZE = 300.0f;
	_world.init(glm::vec4(-WORLD_SIZE, -WORLD_SIZE, WORLD_SIZE, WORLD_SIZE));

	_bulletSchedule.init(1);
	_fpsSchedule.init(500);
	_player1Schedule.init(100);
	_sprinkleSchedule.init(200);
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
		_fpsLimiter.begin(); // mesure frame time

		processInput();

		_camera.update();
		_physicsManager.update();
		updateGameObjects();

		drawGraphics();

		_fps = _fpsLimiter.end(); // delay further calculations based on the target fps
		if (_fpsSchedule.ready()){
			printf("%.2f\n", _fps); // print fps only every 10 frames
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

	if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT)){ // spawn bullets
		if (_bulletSchedule.ready()){
			//madness();
			sprinkle();
		}
	}
}

void MainGame::playerMovement(){
	bool w = false, s = false, a = false, d = false;
	if (_inputManager.isKeyPressed(SDLK_w)){ // player movement
		w = true;
		_player1.objectPhysics->addAcceleration(glm::vec2(0.0f, 1.0f) * _player1.getMovementSpeed());
	}

	if (_inputManager.isKeyPressed(SDLK_s)){
		s = true;
		_player1.objectPhysics->addAcceleration(glm::vec2(0.0f, -1.0f) * _player1.getMovementSpeed());
	}

	if (_inputManager.isKeyPressed(SDLK_a)){
		a = true;
		_player1.objectPhysics->addAcceleration(glm::vec2(-1.0f, 0.0f) * _player1.getMovementSpeed());
	}

	if (_inputManager.isKeyPressed(SDLK_d)){
		d = true;
		_player1.objectPhysics->addAcceleration(glm::vec2(1.0f, 0.0f) * _player1.getMovementSpeed());
	}

	if (w || s || a || d){
	}
}

void MainGame::camaraMovement(){
	const float CAMERA_SPEED = 10.0f;
	const float SCALE_SPEED = 1.02f;
	const float MIN_SCALE = 0.1f;

	if (_inputManager.isKeyPressed(SDLK_UP)){ // camera movement
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, CAMERA_SPEED) / _camera.getScale());
	}

	if (_inputManager.isKeyPressed(SDLK_DOWN)){
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, -CAMERA_SPEED) / _camera.getScale());
	}

	if (_inputManager.isKeyPressed(SDLK_LEFT)){
		_camera.setPosition(_camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0f) / _camera.getScale());
	}

	if (_inputManager.isKeyPressed(SDLK_RIGHT)){
		_camera.setPosition(_camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0f) / _camera.getScale());
	}

	if (_inputManager.isKeyPressed(SDLK_q)){ // camera zoom
		_camera.setScale(_camera.getScale() * SCALE_SPEED);
	}

	if (_inputManager.isKeyPressed(SDLK_e)){
		if (_camera.getScale() > MIN_SCALE){
			_camera.setScale(_camera.getScale() / SCALE_SPEED);
		}
	}
}

void MainGame::updateGameObjects(){

	for (int i = 0; i < _bullets.size(); i++){ //update all bullets game logic
		if (_world.outOfBound(_bullets[i]->objectPhysics->getPosAndBoundary())){ // checks if this game object is out of bounds of the game world //tmp to be replaced by a unified gameobject system
			_bullets[i]->objectPhysics->pushBackAndStop();
		}

		if (_bullets[i]->update()){
			_physicsManager.deleteObject(_bullets[i]->objectPhysics);
			_bullets[i] = _bullets.back();
			_bullets.pop_back();
		}
	}

	if (_world.outOfBound(_player1.objectPhysics->getPosAndBoundary())){
		_player1.objectPhysics->pushBackAndStop();
	}
}

void MainGame::drawGraphics(){

	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_colorProgram.use();
	glActiveTexture(GL_TEXTURE0);
	GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
	glUniform1i(textureLocation, 0); // ben says 1i but I think thats false

	//GLint timeLocation = _colorProgram.getUniformLocation("time");
	//glUniform1f(timeLocation, _time); //set time variable

	GLint pLocation = _colorProgram.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0])); // upload camera Information to the GPU

	_spriteBatch.begin(); //

	static Veng::GLTexture playerTexture = Veng::ResourceManager::getTexture("Textures/Player/p1_hurt.png");
	static Veng::GLTexture bulletTexture = Veng::ResourceManager::getTexture("Textures/Items/keyred.png"); //this is bad

	_spriteBatch.draw(_player1.objectPhysics->getPosAndSize(), _normUV, playerTexture.id, 0.0f, _colorWhite); // draw the player

	int bulletsSize = _bullets.size();
	for (int i = 0; i < bulletsSize; i++){
		Veng::Color bulletColor = speedColor(_bullets[i]->objectPhysics->getSpeedMagnitude(), 5.0f);
		_spriteBatch.draw(_bullets[i]->objectPhysics->getPosAndSize(), _normUV, bulletTexture.id, 0.0f, bulletColor); // draw all bullets
	}

	_spriteBatch.end();

	_spriteBatch.renderBatches();

	glBindTexture(GL_TEXTURE_2D, 0);

	_colorProgram.unUse();

	_window.swapBuffer();
}

void MainGame::spawnBullet(glm::vec2 position, glm::vec2 force){
	float lifeTime = 1000.0f;

	glm::vec2 mousePosition = _inputManager.getMousePosition();
	mousePosition = _camera.convertScreenToWorld(mousePosition);

	Veng::PhysicsInitPackage2D bulletInitPackage;
	float bulletSize = 20.0f;//_random.generateRandomFloat(15.0f, 25.0f);
	bulletInitPackage.mass = bulletSize * bulletSize * 10;
	bulletInitPackage.speed = glm::vec2(0.0f);
	bulletInitPackage.posAndSize = glm::vec4(position.x, position.y, bulletSize, bulletSize); //tmp
	//bulletInitPackage.posAndSize = glm::vec4(0.0f, 0.0f, bulletSize, bulletSize); //tmp
	//bulletInitPackage.posAndSize = glm::vec4(playerPosition.x - bulletSize, playerPosition.y - bulletSize, bulletSize, bulletSize);
	bulletInitPackage.boundaryScale = 0.7;
	bulletInitPackage.friction = 0.97f;// _friction;

	_bullets.emplace_back(new Bullet(lifeTime));
	_physicsManager.addPhysicsObject(_bullets.back()->objectPhysics, bulletInitPackage);

	_bullets.back()->objectPhysics->applyForce(force);
}

void MainGame::madness(){
	int bullets = 1000;
	for (int i = 0; i < bullets; i++){
		float x = _random.generateRandomFloat(-_world.getSize(), _world.getSize());
		float y = _random.generateRandomFloat(-_world.getSize(), _world.getSize());
		glm::vec2 position(x, y);
		glm::vec2 force(0.0f);
		spawnBullet(position, force);
	}
}

void MainGame::sprinkle(){
	if (_sprinkleSchedule.ready()){
		float x = _random.generateRandomFloat(-0.5, 0.5);
		glm::vec2 position( _camera.convertScreenToWorld(_inputManager.getMousePosition()) );
		glm::vec2 force(x, -40000.0f);
		spawnBullet(position, force);
	}
}

Veng::Color MainGame::speedColor(float speed, float max){
	Veng::Color sC;
	//sC.r = std::tanh(speed/max) * 250;
	sC.r = 250;
	sC.g = 100;
	sC.b = 200;
	sC.a = 255; 
	return sC;
}