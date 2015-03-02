#include <cstdlib>

#include "TextureCache.h"
#include "ImageLoader.h"

namespace Veng{

	TextureCache::TextureCache()
	{
	}


	TextureCache::~TextureCache()
	{
	}

	GLTexture TextureCache::getTexture(std::string texturePath){

		auto mit = _textureMap.find(texturePath); // lookup the texture and see if it is in _textureMap

		if (mit == _textureMap.end()){ //check if its in the map
			GLTexture newTexture = ImageLoader::loadPNG(texturePath); // load the texture

			_textureMap.insert(make_pair(texturePath, newTexture)); // insert the texture

			printf("Loaded new texture\n");
			return newTexture;
		}
		else{
			printf("Used cached texture\n");
			return mit->second;
		}
	}

}