#include "ImageLoader.h"
#include <Logging/Log.h>

#include <Helpers/NullPtr.h>

namespace
{
	#include <stblib/stb_image.c>
}

namespace baselib { namespace graphics {

	boost::shared_ptr<ImageLoader> ImageLoader::create()
	{
		return boost::shared_ptr<ImageLoader>(new ImageLoader());
	}

	ImageLoader::ImageLoader()
	{
		LOG_VERBOSE << "ImageLoader constructor";
	}

	ImageLoader::~ImageLoader()
	{
		LOG_VERBOSE << "ImageLoader destructor";
	}

	namespace
	{
		void flipY(unsigned char* pData, int iX, int iY, int iBytesPerPixel)
		{
			int iRowSize = iX * iBytesPerPixel;
			unsigned char *pRowOne = 0;
			unsigned char *pRowTwo = 0;
			unsigned char *pRowTemp = new unsigned char[iRowSize];
			for (int iRow = 0; iRow < iY/2; ++iRow)
			{
				pRowOne = pData + (iRow * iRowSize);
				pRowTwo = pData + ((iY-iRow-1) * iRowSize);
				memcpy(pRowTemp, pRowOne, iRowSize);
				memcpy(pRowOne, pRowTwo, iRowSize);
				memcpy(pRowTwo, pRowTemp, iRowSize);
			}
			delete []pRowTemp;
		}
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
		flipY(pData, iX, iY, iChannels);

		// Create image object and add to cache
		auto spImage = Image::create(iX, iY, iBPP, pData);
		m_ImageCache.add(sCanonicalPath, spImage);
		return spImage;
	}

} }