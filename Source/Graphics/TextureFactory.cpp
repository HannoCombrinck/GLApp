#include "TextureFactory.h"

#include <GL/glew.h>
#include <Helpers/NullPtr.h>
#include <Logging/Log.h>
#include <Graphics/ImageLoader.h>

namespace baselib { namespace graphics {

	TextureFactory::TextureFactory()
	{
		LOG_VERBOSE << "TextureFactory constructor";
	}

	TextureFactory::~TextureFactory()
	{
		LOG_VERBOSE << "TextureFactory destructor";
	}

	boost::shared_ptr<Texture> TextureFactory::createTexture(const fs::path& fsPath)
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


		// Load image from file
		// Create texture from image
		// Return texture

		LOG_INFO << "TODO";
		assert(false);
		return null_ptr;
	}

	boost::shared_ptr<Texture> TextureFactory::createTexture(const boost::shared_ptr<Image>& spImage)
	{
		glActiveTexture(GL_TEXTURE0);

		unsigned int uID;
		glGenTextures(1, &uID);
		glBindTexture(GL_TEXTURE_2D, uID);

		// Using hard coded defaults to get things up and running.
		// TODO: Wrap texture parameters, types, formats etc. 
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, spImage->getWidth(), spImage->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, (const GLvoid*) spImage->getData());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		return boost::shared_ptr<Texture>(new Texture(uID, Texture::TEXTURE_2D));
	}

} }