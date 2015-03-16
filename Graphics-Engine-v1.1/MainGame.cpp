#include <iostream>
#include <string>
#include <cstdlib>

#include "MainGame.h"
#include <Veng/Errors.h>
#include <Veng/ResourceManager.h>

MainGame::MainGame() : 
	_bulletSpawnable(true),
	_screenWidth(1920),
	_screenHeight(1080),
	_gameState(GameState::PLAY),
	_maxFPS(90.0f),
	_time(0),
	_vsyncFlag(Veng::VSYNC_ON),
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

	const glm::vec2 PLAYER_SPAWN(0.0f, 0.0f);
	_player1.init(glm::vec4(PLAYER_SPAWN.x, PLAYER_SPAWN.y, 69.0f, 92.0f), glm::vec2(0.0f, 0.0f), 6348.0f, 5.0f, 0.8, 100.0f);
	_physicsManager.addPhysicsObject(_player1.objectPhysics);

	_colorWhite.setColor(255, 255, 255, 255);

	const float WORLD_SIZE = 400.0f;
	_world.init(glm::vec4(-WORLD_SIZE, -WORLD_SIZE, WORLD_SIZE, WORLD_SIZE));
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
		_time += 0.05f;

		_camera.update();
		_physicsManager.update();

		int bulletsSize = _bullets.size();
		for (int i = 0; i < bulletsSize;){ //update all bullets
			moveObject(_bullets[i]->objectPhysics, _bullets[i]->objectPhysics->getDirection());
			if (_bullets[i]->update()){
				deleteObject(_bullets, i);

				bulletsSize--;
			}
			else{
				i++;
			}
		}

		drawGraphics();

		_fps = _fpsLimiter.end();

		frameCounter++;
		if (frameCounter == 10){
			printf("%.2f\n", _fps); // print fps only every 10 frames
			frameCounter = 0;

			_bulletSpawnable = true;
		}
	}
}

void MainGame::processInput(){
	SDL_Event evnt;

	const float CAMERA_SPEED = 10.0f;
	const float SCALE_SPEED = 1.02f;
	const float MIN_SCALE = 0.1f;

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

	_player1.objectPhysics->setSpeed(_player1.getMovementSpeed());
	if (_inputManager.isKeyPressed(SDLK_w)){ // player movement
		moveObject(_player1.objectPhysics, glm::vec2(0.0f, 1.0f));
	}

	if (_inputManager.isKeyPressed(SDLK_s)){
		moveObject(_player1.objectPhysics, glm::vec2(0.0f, -1.0f));
	}

	if (_inputManager.isKeyPressed(SDLK_a)){
		moveObject(_player1.objectPhysics, glm::vec2(-1.0f, 0.0f));
	}

	if (_inputManager.isKeyPressed(SDLK_d)){
		moveObject(_player1.objectPhysics, glm::vec2(1.0f, 0.0f));
	}
	_player1.objectPhysics->setSpeed(0.0f);

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

	if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT)){ // spawn bullets
		if (_bulletSpawnable){
			spawnBullet();
		}
	}
}

void MainGame::drawGraphics(){

	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_colorProgram.use();
	glActiveTexture(GL_TEXTURE0);
	GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
	glUniform1f(textureLocation, 0); // ben says 1i but I think thats false

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
		_spriteBatch.draw(_bullets[i]->objectPhysics->getPosAndSize(), _normUV, bulletTexture.id, 0.0f, _colorWhite); // draw all bullets
	}

	_spriteBatch.end(); //

	_spriteBatch.renderBatches();

	glBindTexture(GL_TEXTURE_2D, 0);

	_colorProgram.unUse();

	_window.swapBuffer();
}

template<typename T>
void MainGame::moveObject(T* physicsObject, glm::vec2 direction){

	physicsObject->move(direction);

	Veng::ObjectPhysics2D* collisionObject = _physicsManager.findIntersection(physicsObject);
	if (collisionObject != nullptr){
		_physicsManager.collide(physicsObject, collisionObject);
	}

	if (_world.outOfBound(physicsObject->getPosAndSize(), direction)){
		physicsObject->setDirection(direction);
		physicsObject->move(direction);
	}
}

template<typename T>
void MainGame::deleteObject(std::vector<T*>& objectVec, int vecPosition){

	_physicsManager.deletePhysicsObject(objectVec[vecPosition]->objectPhysics);

	objectVec[vecPosition] = objectVec.back();
	objectVec.pop_back();
}

void MainGame::spawnBullet(){
	glm::vec2 mousePosition = _inputManager.getMousePosition();
	mousePosition = _camera.convertScreenToWorld(mousePosition);

	// std::printf("Mouse: PosX: %f, PosY: %f\n", mousePosition.x, mousePosition.y);

	glm::vec2 playerPosition = _player1.objectPhysics->getPosition();
	glm::vec2 direction = mousePosition - playerPosition;
	direction = glm::normalize(direction);

	float bulletSize = 10.0f;//_random.generateRandomFloat(10.0f, 20.0f);
	float lifeTime = 1000.0f;
	float bulletMass = bulletSize * bulletSize;
	float bulletSpeed = 8.0f;

	_bullets.emplace_back(new Bullet(glm::vec4(playerPosition.x - bulletSize, playerPosition.y - bulletSize, bulletSize, bulletSize), direction, bulletMass, bulletSpeed, 0.7, lifeTime));

	_physicsManager.addPhysicsObject(_bullets.back()->objectPhysics);
	_bulletSpawnable = false;
}