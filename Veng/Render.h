#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>

#include "Sprite.h"
#include "SpriteBatch.h"
#include "Vertex.h"
#include "Window.h"
#include "GLSLProgram.h"
#include "Camera2D.h"
#include "ObjectPhysics2D.h"


namespace Veng{

class Render
{
public:
	Render();
	~Render();

	void init(std::string windowName, int screenWidth, int windowFlags, unsigned int currentFlags, unsigned char vsyncFlag);
	void linkRenderToPhysics(std::vector<ObjectPhysics2D>* objects2D);

	void update();
	void addTexture(std::string textureLocation); // should be called and stored in a static unsigned int if used more than once

	Camera2D camera;

private:
	void initShaders();

	Window _window;
	GLSLProgram _colorProgram;
	SpriteBatch _spriteBatch;

	Color speedColor(float speed, float max);

	int _screenWidth;
	int _screenHeight;

	std::vector<ObjectPhysics2D>*_objects2D;

	glm::vec4 _normUV;
	Veng::Color _colorWhite;
};

}