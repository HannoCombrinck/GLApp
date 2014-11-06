#include "Texture.h"

#include <Graphics/Image.h>
#include <Logging/Log.h>
#include <Helpers/ResourceCache.h>
#include <GL/glew.h>

// GL_MAX_TEXTURE_SIZE

namespace baselib { namespace graphics {

	unsigned int Texture::m_uCurrentlyBound = ~0;
	unsigned int Texture::m_uActiveUnit = ~0;

	namespace
	{
		ResourceCache<Texture> m_TextureCache;
	}

	boost::shared_ptr<Texture> Texture::load(const fs::path& fsPath)
	{
		// Check if image file exists
		if (!fs::exists(fsPath))
		{
			LOG_ERROR << "Cannot find image " << fsPath;
			assert(false);
		}

		// Get canonical path
		std::string sCanonicalPath = fs::canonical(fsPath).string();

		// Check texture cache
		if (auto sp = m_TextureCache.get(sCanonicalPath))
			return sp;

		auto spImage = Image::load(fsPath);
		auto spTexture = Texture::create(spImage);

		// Add to texture cache
		m_TextureCache.add(sCanonicalPath, spTexture);

		return spTexture;
	}

	boost::shared_ptr<Texture> Texture::create(const boost::shared_ptr<Image>& spImage)
	{
		glActiveTexture(GL_TEXTURE0);

		unsigned int uID;
		glGenTextures(1, &uID);
		glBindTexture(GL_TEXTURE_2D, uID);

		// Using hard coded defaults to get things up and running.
		// TODO: Wrap texture parameters, types, formats etc. 
		if (spImage->getBPP() == 128)
		{
			glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, spImage->getWidth(), spImage->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, (const GLvoid*)spImage->getData());
		}
		if (spImage->getBPP() == 32)
		{
			glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, spImage->getWidth(), spImage->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, (const GLvoid*)spImage->getData());
		}
		else if (spImage->getBPP() == 24)
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

		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		float fAnisotropicMax = 0.0f;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &fAnisotropicMax);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, fAnisotropicMax);

		return boost::shared_ptr<Texture>(new Texture(uID, Texture::TEXTURE_2D, spImage->getWidth(), spImage->getHeight(), spImage->getBPP()));
	}

	boost::shared_ptr<Texture> Texture::createRenderTarget(const boost::shared_ptr<Image>& spImage)
	{
		glActiveTexture(GL_TEXTURE0);

		unsigned int uID;
		glGenTextures(1, &uID);
		glBindTexture(GL_TEXTURE_2D, uID);

		// Hard code defaults for now
		if (spImage->getBPP() == 128) // For GBuffer colour targets
		{
			glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, spImage->getWidth(), spImage->getHeight(), 0, GL_RGBA, GL_FLOAT, (const GLvoid*)spImage->getData());
		}
		else if (spImage->getBPP() == 32)
		{
			glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, spImage->getWidth(), spImage->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, (const GLvoid*)spImage->getData());
		}
		else if (spImage->getBPP() == 24) // For GBuffer depth target
		{
			glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, spImage->getWidth(), spImage->getHeight(), 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, (const GLvoid*)spImage->getData());
		}
		else
		{
			assert(false);
		}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_POINT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_POINT);

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

	void Texture::bind(unsigned int uUnit /*= 0*/)
	{
		if (m_uID == m_uCurrentlyBound)
			return;

		unsigned int uGLUnit = GL_TEXTURE0 + uUnit;
		if (m_uActiveUnit != uGLUnit)
		{
			glActiveTexture(uGLUnit);
			m_uActiveUnit = uGLUnit;
		}

		glBindTexture(GL_TEXTURE_2D, m_uID);
		m_uCurrentlyBound = m_uID;
	}

} }