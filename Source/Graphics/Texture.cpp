#include "Texture.h"

#include <Logging/Log.h>
#include <GL/glew.h>

// GL_MAX_TEXTURE_SIZE

namespace baselib { namespace graphics {

	Texture::Texture(unsigned int uID)
		: m_uID(uID)
	{
		LOG_VERBOSE << "Texture constructor";
	}

	Texture::~Texture()
	{
		LOG_VERBOSE << "Texture destructor";
	}

} }