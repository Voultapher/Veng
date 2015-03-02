#pragma once

#include <string>

#include "GLTexture.h"

namespace Veng{

	class ImageLoader
	{
	public:
		static GLTexture loadPNG(std::string filePath);
	};

}