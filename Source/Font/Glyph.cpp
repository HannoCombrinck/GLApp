#include "Glyph.h"

#include <Logging/Log.h>
#include <ft2build.h>
#include FT_FREETYPE_H

namespace baselib { namespace font {

	Glyph::Glyph(unsigned char uChar, unsigned int uWidth, unsigned int uHeight, unsigned int uAdvance, unsigned int uBearingX, unsigned int uBearingY, const Vec2& vUVMin, const Vec2& vUVMax)
		: m_uChar(uChar)
		, m_uWidth(uWidth)
		, m_uHeight(uHeight)
		, m_uAdvance(uAdvance)
		, m_uBearingX(uBearingX)
		, m_uBearingY(uBearingY)
		, m_vUVMin(vUVMin)
		, m_vUVMax(vUVMax)
	{
		LOG_VERBOSE << "Glyph constructor";
	}

	Glyph::~Glyph()
	{
		LOG_VERBOSE << "Glyph destructor";
	}

} }