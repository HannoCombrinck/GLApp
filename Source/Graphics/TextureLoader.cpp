#include "TextureLoader.h"

#include <GL/glew.h>
#include <Helpers/NullPtr.h>
#include <Logging/Log.h>
#include <Graphics/ImageLoader.h>

namespace baselib { namespace graphics {

	TextureLoader::TextureLoader()
	{
		LOG_VERBOSE << "TextureLoader constructor";
	}

	TextureLoader::~TextureLoader()
	{
		LOG_VERBOSE << "TextureLoader destructor";
	}

	boost::shared_ptr<Texture> TextureLoader::loadTexture(const fs::path& fsPath)
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

} }