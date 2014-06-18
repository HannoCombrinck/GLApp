#include "ImageLoader.h"
#include <Logging/Log.h>

#include <Helpers/NullPtr.h>
#include <gli/gli.hpp>

namespace baselib { namespace graphics {

	ImageLoader::ImageLoader()
	{
		LOG_VERBOSE << "ImageLoader constructor";
	}

	ImageLoader::~ImageLoader()
	{
		LOG_VERBOSE << "ImageLoader destructor";
	}

	boost::shared_ptr<Image> ImageLoader::loadImage(const fs::path& fsPath)
	{
		// Check if image file exists
		if (!fs::exists(fsPath))
		{
			LOG_ERROR << "Cannot find image " << fsPath;
			assert(false);
		}

		// Get canonical path
		std::string sCanonicalPath = fs::canonical(fsPath).string();

		// Check image cache
		if (auto sp = m_ImageCache.get(sCanonicalPath))
			return sp;

		// Load image from file using GLI
		gli::texture2D gliTex(gli::load_dds(sCanonicalPath.c_str()));

		
		return null_ptr;
	}

} }