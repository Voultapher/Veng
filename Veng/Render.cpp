#include "Render.h"

#include <glm\glm.hpp>
#include <GL\glew.h>

#include "ResourceManager.h"
#include "Physics2D.h"

namespace Veng{

Render::Render() :
	_normUV(0.0f, 0.0f, 1.0f, 1.0f)
{
}


Render::~Render()
{
}

void Render::init(std::string windowName, int screenWidth, int screenHeight, unsigned int windowFlags, unsigned char vsyncFlag){

	_screenWidth = screenWidth;
	_screenHeight = screenHeight;

	_window.create("Graphics-Engine", _screenWidth, _screenHeight, windowFlags, vsyncFlag);
	camera.init(_screenWidth, _screenHeight);
	_spriteBatch.init();
	initShaders();

	_colorWhite.setColor(255, 255, 255, 255);
}

void Render::initShaders(){
	_colorProgram.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexColor");
	_colorProgram.addAttribute("vertexUV");
	_colorProgram.linkShaders();
}

void Render::linkRenderToPhysics(std::vector<ObjectPhysics2D>* objects2D){
	_objects2D = objects2D;
}

void Render::update(){
	camera.update();

	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_colorProgram.use();
	glActiveTexture(GL_TEXTURE0);
	GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
	glUniform1i(textureLocation, 0); // ben says 1i but I think thats false

	//GLint timeLocation = _colorProgram.getUniformLocation("time");
	//glUniform1f(timeLocation, _time); //set time variable

	GLint pLocation = _colorProgram.getUniformLocation("P");
	glm::mat4 cameraMatrix = camera.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0])); // upload camera Information to the GPU

	_spriteBatch.begin(); //

	for (auto& object : (*_objects2D)){
		_spriteBatch.draw(object.getPosAndSize(), _normUV, object.getTexture().id, 0.0f, _colorWhite);
	}

	_spriteBatch.end();

	_spriteBatch.renderBatches();

	glBindTexture(GL_TEXTURE_2D, 0);

	_colorProgram.unUse();

	_window.swapBuffer();
}

Color Render::speedColor(float speed, float max){
	Veng::Color sC;
	sC.r = 250;
	sC.g = std::tanh(max / (speed + 1.0f)) * 250;
	sC.b = std::tanh(max / (speed + 1.0f)) * 250;
	sC.a = 255;
	return sC;
}

}