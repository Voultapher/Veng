#include <algorithm>

#include "SpriteBatch.h"

namespace veng{

SpriteBatch::SpriteBatch() :
_vbo(0),
_vao(0)
{

}


SpriteBatch::~SpriteBatch()
{
	
}

void SpriteBatch::init(){
	createVertexArray();
}

void SpriteBatch::begin(GlyphSortType sortType /* = GlyphSortType::TEXTURE */){
	_sortType = sortType;
	_renderBatches.clear();
	_glyphs.clear();
}

void SpriteBatch::end(){
	sortGlyphs();
	createRenderBatches();
}

void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint textureId, float depth, const ColorRGBA8& color){

	_glyphs.emplace_back(destRect, uvRect, textureId, depth, color);
}

void SpriteBatch::renderBatches(){

	glBindVertexArray(_vao);

	int renderBatchSize = _renderBatches.size();
	for (int i = 0; i < renderBatchSize; i++){
		glBindTexture(GL_TEXTURE_2D, _renderBatches[i].texture);

		glDrawArrays(GL_TRIANGLES, _renderBatches[i].offset, _renderBatches[i].numVertices);
	}
	glBindVertexArray(0);
}

void SpriteBatch::createRenderBatches(){
	if (_glyphs.empty()){
		return;
	}

	std::vector<Vertex> vertices;
	vertices.resize(_glyphs.size() * 6);

	int offset = 0;
	int cv = 0; // current vertex
	_renderBatches.emplace_back(offset, 6, _glyphs[0].texture); // filling the first vector slot
	vertices[cv++] = _glyphs[0].topLeft;
	vertices[cv++] = _glyphs[0].bottomLeft;
	vertices[cv++] = _glyphs[0].bottomRight;
	vertices[cv++] = _glyphs[0].bottomRight;
	vertices[cv++] = _glyphs[0].topRight;
	vertices[cv++] = _glyphs[0].topLeft;
	offset += 6;

	int glyphsSize = _glyphs.size();
	for (int cg = 1; cg < glyphsSize; cg++){
		if (_glyphs[cg].texture != _glyphs[cg - 1].texture){ // as we sorted the glyphs vector by texture, same texture sprite will be next to each other
			_renderBatches.emplace_back(offset, 6, _glyphs[cg].texture); // only add new Batch if it has a new texture
		}
		else{
			_renderBatches.back().numVertices += 6; // else adjust the size of numVertices
		}
		
		vertices[cv++] = _glyphs[cg].topLeft; // add the vertex position to the whole vector of vertices
		vertices[cv++] = _glyphs[cg].bottomLeft;
		vertices[cv++] = _glyphs[cg].bottomRight;
		vertices[cv++] = _glyphs[cg].bottomRight;
		vertices[cv++] = _glyphs[cg].topRight;
		vertices[cv++] = _glyphs[cg].topLeft;
		offset += 6;
	}

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW); // orpha the buffer
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data()); // upload the data to the GPU

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SpriteBatch::createVertexArray(){
	if (_vao == 0){
		glGenVertexArrays(1, &_vao);
	}
	glBindVertexArray(_vao);

	if (_vbo == 0){
		glGenBuffers(1, &_vbo);
	}
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	glEnableVertexAttribArray(0); // tell opengl that we want to use the first attribute array
	glEnableVertexAttribArray(1); // there is more than position so more attribute arrays
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position)); // this is the position attribute pointer

	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color)); // this is the color attribute pointer

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv)); // this is the uv attribute pointer

	glBindVertexArray(0);

}

void SpriteBatch::sortGlyphs(){
	switch (_sortType) {
	case GlyphSortType::FRONT_TO_BACK:
		std::stable_sort(_glyphs.begin(), _glyphs.end(), compareFrontToBack);
		break;
	case GlyphSortType::BACK_TO_FRONT:
		std::stable_sort(_glyphs.begin(), _glyphs.end(), compareBackToFront);
		break;
	case GlyphSortType::TEXTURE:
		std::stable_sort(_glyphs.begin(), _glyphs.end(), compareTexture);
		break;

	}
}

bool SpriteBatch::compareFrontToBack(const Glyph& a, const Glyph& b){
	return (a.depth < b.depth);
}

bool SpriteBatch::compareBackToFront(const Glyph& a, const Glyph& b){
	return (a.depth > b.depth);
}

bool SpriteBatch::compareTexture(const Glyph& a, const Glyph& b){
	return (a.texture < b.texture);
}

}