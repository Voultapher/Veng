#pragma once

#include <string>

#include "GLTexture.h"

namespace veng{

	class ImageLoader
	{
	public:
		static GLTexture loadPNG(std::string filePath);
	};

}