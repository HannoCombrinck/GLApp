#include "Texture.h"

#include <Graphics/Image.h>
#include <Logging/Log.h>
#include <GL/glew.h>

// GL_MAX_TEXTURE_SIZE

namespace baselib { namespace graphics {

	boost::shared_ptr<Texture> Texture::create(const boost::shared_ptr<Image>& spImage)
	{
		glActiveTexture(GL_TEXTURE0);

		unsigned int uID;
		glGenTextures(1, &uID);
		glBindTexture(GL_TEXTURE_2D, uID);

		// Using hard coded defaults to get things up and running.
		// TODO: Wrap texture parameters, types, formats etc. 
		if (spImage->getBPP() == 24)
		{
			glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, spImage->getWidth(), spImage->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, (const GLvoid*)spImage->getData());
		}
		else if (spImage->getBPP() == 8)
		{
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, spImage->getWidth(), spImage->getHeight(), 0, GL_RED, GL_UNSIGNED_BYTE, (const GLvoid*)spImage->getData());
		}
		else
		{
			assert(false);
		}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		return boost::shared_ptr<Texture>(new Texture(uID, Texture::TEXTURE_2D, spImage->getWidth(), spImage->getHeight(), spImage->getBPP()));
	}

	Texture::Texture(unsigned int uID, TextureType eType, int iWidth, int iHeight, int iBPP)
		: m_uID(uID)
		, m_eType(eType)
		, m_iWidth(iWidth)
		, m_iHeight(iHeight)
		, m_iBPP(iBPP)
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