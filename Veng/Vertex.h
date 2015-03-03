#pragma once 

#include <GL/glew.h>

namespace Veng{

struct Position{
	float x;
	float y;
};

struct Color{
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;

	void setColor(GLubyte R, GLubyte G, GLubyte B, GLubyte A){
		r = R;
		g = G;
		b = B;
		a = A;
	}
};

struct UV{
	float u;
	float v;
};

struct Vertex{
	Position position;

	Color color;

	UV uv;

	void setPosition(float x, float y){
		position.x = x;
		position.y = y;
	}

	void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a){
		color.r = r;
		color.g = g;
		color.b = b;
		color.a = a;
	}

	void setUV(float u, float v){
		uv.u = u;
		uv.v = v;
	}
};

}