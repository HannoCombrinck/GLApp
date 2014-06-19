#include "ImageLoader.h"
#include <Logging/Log.h>

#include <Helpers/NullPtr.h>

namespace
{
	#include <stblib/stb_image.c>
}

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

		// Load the image using stblib
		int iX = 0;
		int iY = 0;
		int iChannels = 0;
		unsigned char* pData = stbi_load(sCanonicalPath.c_str(), &iX, &iY, &iChannels, 0);
		int iBPP = iChannels*8; // Assume 8 bits per pixel.

		return boost::shared_ptr<Image>(new Image(iX, iY, iBPP, pData));
	}

} }