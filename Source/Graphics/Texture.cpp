#include "Texture.h"

#include <Graphics/Image.h>
#include <Logging/Log.h>
#include <GL/glew.h>

// GL_MAX_TEXTURE_SIZE

namespace baselib { namespace graphics {

	boost::shared_ptr<Texture> Texture::create( const boost::shared_ptr<Image>& spImage )
	{
		glActiveTexture(GL_TEXTURE0);

		unsigned int uID;
		glGenTextures(1, &uID);
		glBindTexture(GL_TEXTURE_2D, uID);

		// Using hard coded defaults to get things up and running.
		// TODO: Wrap texture parameters, types, formats etc. 
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, spImage->getWidth(), spImage->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, (const GLvoid*)spImage->getData());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		return boost::shared_ptr<Texture>(new Texture(uID, Texture::TEXTURE_2D));
	}

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
		glBindTexture(GL_TEXTURE_2D, m_uID);
	}

} }