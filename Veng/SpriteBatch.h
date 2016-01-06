#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

#include "Vertex.h"

namespace veng{

	enum class GlyphSortType {
		NONE,
		FRONT_TO_BACK,
		BACK_TO_FRONT,
		TEXTURE
	};

class Glyph{
public:
	explicit Glyph() { };
	explicit Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint textureId, const float depth, const ColorRGBA8& color) :
		texture(textureId), depth(depth)
	{

		topLeft.color = color;
		topLeft.setPosition(destRect.x, destRect.y + destRect.w);
		topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

		bottomLeft.color = color;
		bottomLeft.setPosition(destRect.x, destRect.y);
		bottomLeft.setUV(uvRect.x, uvRect.y);

		topRight.color = color;
		topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
		topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

		bottomRight.color = color;
		bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
		bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);
	}

	GLuint texture;
	float depth;

	Vertex topLeft;
	Vertex bottomLeft;
	Vertex topRight;
	Vertex bottomRight;
};

class RenderBatch{
public:
	RenderBatch(GLuint Offset, GLuint NumVertices, GLuint Texture) :
		offset(Offset),
		numVertices(NumVertices),
		texture(Texture)
	{
	}
	GLuint offset;
	GLuint numVertices;
	GLuint texture;
};


class SpriteBatch
{
public:
	SpriteBatch();
	~SpriteBatch();

	void init();

	void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
	void end();
	
	void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint textureId, float depth, const ColorRGBA8& color);

	void renderBatches();

private:
	void createRenderBatches();
	void createVertexArray();
	void sortGlyphs();

	static bool compareFrontToBack(const Glyph& a, const Glyph& b);
	static bool compareBackToFront(const Glyph& a, const Glyph& b);
	static bool compareTexture(const Glyph& a, const Glyph& b);

	GLuint _vbo;
	GLuint _vao;

	GlyphSortType _sortType;

	std::vector<Glyph> _glyphs;
	std::vector<RenderBatch> _renderBatches;
};

}