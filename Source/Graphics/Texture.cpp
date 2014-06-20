#include "Texture.h"

#include <Logging/Log.h>
#include <GL/glew.h>

// GL_MAX_TEXTURE_SIZE

namespace baselib { namespace graphics {

	Texture::Texture(unsigned int uID, TextureType eType)
		: m_uID(uID)
		, m_eType(eType)
	{
		LOG_VERBOSE << "Texture constructor";
	}

	Texture::~Texture()
	{
		LOG_VERBOSE << "Texture destructor";
		glDeleteTextures(1, &m_uID);
		m_uID = ~0;
	}

	void Texture::bind()
	{
		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, m_uID);
	}

	void Texture::unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

} }