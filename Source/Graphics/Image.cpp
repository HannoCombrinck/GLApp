#include "Image.h"

#include <Logging/Log.h>

namespace baselib { namespace graphics {

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