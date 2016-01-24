#include "Image.h"

#include <Logging/Log.h>
#include <Core/ResourceCache.h>

namespace
{
	#include <stblib/stb_image.c>
}

namespace baselib { namespace graphics {

	namespace
	{
		ResourceCache<Image> m_ImageCache;

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

	std::shared_ptr<Image> Image::load(const fs::path& fsPath)
	{
		// Check if image file exists
		if (!fs::exists(fsPath))
		{
			LOG_ERROR << "Cannot find image " << fsPath;
			assert(false);
		}

		LOG_INFO << "Loading: " << fs::canonical(fsPath);

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

	std::shared_ptr<Image> Image::create(int iWidth, int iHeight, int iBPP, unsigned char* pData )
	{
		auto spImage = std::shared_ptr<Image>(new Image(iWidth, iHeight, iBPP, pData));
		return spImage;
	}

	Image::Image(int iWidth, int iHeight, int iBPP, unsigned char* pData)
		: m_iWidth(iWidth)
		, m_iHeight(iHeight)
		, m_iBPP(iBPP)
		, m_pData(pData)
	{
		LOG_VERBOSE << "Image constructor";
	}

	Image::~Image()
	{
		LOG_VERBOSE << "Image destructor";
		if (m_pData)
		{
			delete []m_pData;
			m_pData = 0;
		}
	}

} }