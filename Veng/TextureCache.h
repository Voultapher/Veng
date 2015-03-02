#pragma once

#include <map>
#include <string>

#include "GLTexture.h"

namespace Veng{

	class TextureCache
	{
	public:
		TextureCache();
		~TextureCache();

		GLTexture getTexture(std::string texturePath);

	private:
		std::map<std::string, GLTexture> _textureMap;
	};

}