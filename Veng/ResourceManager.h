#pragma once

#include <string>

#include "TextureCache.h"

namespace veng{

	class ResourceManager
	{
	public:

		static GLTexture getTexture(std::string texturePath);

	private:
		static TextureCache _textureCache;
	};

}