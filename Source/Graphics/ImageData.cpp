#include "ImageData.h"

#include <Logging/Log.h>

namespace
{
	//#include <stblib/stb_image.c>
}

namespace baselib { namespace graphics {

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

	std::shared_ptr<ImageData> ImageData::load(const fs::path& fsPath)
	{
		// Check if image file exists
		if (!fs::exists(fsPath))
		{
			LOG_ERROR << "Cannot find image " << fsPath;
			assert(false);
		}

		LOG_INFO << "Loading: " << fs::canonical(fsPath);

		// Load the image using stblib
		int iX = 0;
		int iY = 0;
		int iChannels = 0;
		unsigned char* pData = 0;//stbi_load(fsPath.string().c_str(), &iX, &iY, &iChannels, 0);
		PixelFormat eFormat = RGBA8; // TODO: Get correct format - for now assume RGBA8
		flipY(pData, iX, iY, iChannels);

		return ImageData::create(iX, iY, eFormat, pData);
	}

	std::shared_ptr<ImageData> ImageData::create(unsigned int uWidth, unsigned int uHeight, PixelFormat eFormat, unsigned char* pData)
	{
		auto spImage = std::shared_ptr<ImageData>(new ImageData(uWidth, uHeight, eFormat, pData));
		return spImage;
	}

	ImageData::ImageData(unsigned int uWidth, unsigned int uHeight, PixelFormat eFormat, unsigned char* pData)
		: m_uWidth(uWidth)
		, m_uHeight(uHeight)
		, m_eFormat(eFormat)
		, m_pData(pData)
	{
		LOG_VERBOSE << "ImageData constructor";
	}

	ImageData::~ImageData()
	{
		LOG_VERBOSE << "ImageData destructor";
		if (m_pData)
		{
			delete []m_pData;
			m_pData = 0;
		}
	}

} }