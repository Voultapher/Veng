#pragma once

#include <string>

#include "TextureCache.h"

class ResourceManager
{
public:

	static GLTexture getTexture(std::string texturePath);

private:
	static TextureCache _textureCache;
};

