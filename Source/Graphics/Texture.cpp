#include "Texture.h"

#include <Logging/Log.h>

namespace baselib { namespace graphics {

	Texture::Texture()
	{
		LOG_VERBOSE << "Texture constructor";
	}

	Texture::~Texture()
	{
		LOG_VERBOSE << "Texture destructor";
	}

} }