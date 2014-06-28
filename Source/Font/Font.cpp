#include "Font.h"

#include <Helpers/NullPtr.h>
#include <Graphics/Texture.h>
#include <Logging/Log.h>
#include <Font/Glyph.h>
#include <ft2build.h>
#include FT_FREETYPE_H

using namespace baselib::graphics;

namespace baselib { namespace font {

	Font::Font(FT_FaceRec_ *ftFace, const Vec2& vAtlasSize)
		: m_FTFace(ftFace)
	{
		LOG_VERBOSE << "Font constructor";

		unsigned int uCharacter = 'A';
		FT_UInt uIndex = FT_Get_Char_Index(m_FTFace, uCharacter);
		if (uIndex == 0)
		{
			LOG_ERROR << "Glyph not found for character: " << uCharacter;
			assert(false);
		}

		int iFlags = 0;
		FT_Error ftError = FT_Load_Glyph(m_FTFace, uIndex, iFlags); // This loads the glyph into m_FTFace->glyph (i.e. only the last loaded glyph is stored)
		if (ftError)
		{
			LOG_ERROR << "Error loading Glyph with index: " << uIndex;
			assert(false);
		}

		FT_Glyph_Format ftGF = m_FTFace->glyph->format;
		if (ftGF != FT_GLYPH_FORMAT_BITMAP) // Ok to convert to ftBitmap immediately
		{
			// Check FT_Render_Mode for available modes (anti-aliased, mono etc.)
			FT_GlyphSlot ftSlot = m_FTFace->glyph;
			FT_Error ftError = FT_Render_Glyph(ftSlot, FT_RENDER_MODE_NORMAL); // This renders the glyph into glyph->bitmap and positions are in glyph->bitmap_left and glyph->bitmap_top
			if (ftError)
			{
				LOG_ERROR << "Error rendering glyph bitmap";
				assert(false);
			}

			// glyph->bitmap now contains the rendered glyph

			//ftSlot->bitmap
			//ftSlot->bitmap_left
			//ftSlot->bitmap_top
			//ftSlot->advance.x
			//ftSlot->advance.y

			FT_Glyph_Metrics ftGM = ftSlot->metrics;
			unsigned int uWidth = unsigned int(ftGM.width) * 64;	// width of bitmap to be rendered into atlas
			unsigned int uHeight = unsigned int(ftGM.height) * 64; // height of bitmap to be rendered into atlas
			unsigned int uAdvance = unsigned int(ftGM.horiAdvance) * 64; // width of character when rendered in string - difference between cursor left of character and right of char
			unsigned int uBearingX = unsigned int(ftGM.horiBearingX) * 64; // distance from cursor to left border of character
			unsigned int uBearingY = unsigned int(ftGM.horiBearingY) * 64; // distance from baseline to top of border of character

			// All metrics measured in 1/64th of a pixel i.e. iWidth * 64 = width in pixels - unless FT_LOAD_NO_SCALE is used (check freetype docs)

			// Current cursor position is a position on the baseline
			// Glyph should be rendered at position (iBearingX, iBearingY) relative to current cursor position

			FT_Bitmap ftBitmap = ftSlot->bitmap;

			auto spGlyph = boost::shared_ptr<Glyph>(new Glyph('A', uWidth, uHeight, uAdvance, uBearingX, uBearingY, Vec2(0.0f, 0.0f), Vec2(1.0, 1.0)));
		}

		// Kerning
		bool bHasKerning = false;
		if (FT_HAS_KERNING(m_FTFace))
			bHasKerning = true;

		FT_Vector ftKerning;
		unsigned int uIndexLeft = 0;
		unsigned int uIndexRight = 1;
		// When uIndexLeft is 0 then the kerning is always 0
		FT_Get_Kerning(m_FTFace, uIndexLeft, uIndexRight, FT_KERNING_DEFAULT, &ftKerning);  // FT_KERNING_DEFAULT - kerning is in units of 1/64th of a pixel width


	}

	Font::~Font()
	{
		LOG_VERBOSE << "Font destructor";
	}

	namespace
	{
		// Render the bitmap for uChar and store in FT_Face slot i.e. bitmap data for uChar is rendered to m_FTFace->glyph->bitmap
		void createBitmap(FT_Face ftFace, unsigned char uChar)
		{
			FT_UInt uIndex = FT_Get_Char_Index(ftFace, uChar);
			if (uIndex == 0)
			{
				LOG_ERROR << "Glyph not found for character: " << uChar;
				assert(false);
			}

			int iFlags = 0;
			FT_Error ftError = FT_Load_Glyph(ftFace, uIndex, iFlags); // This loads the glyph into ftFace->glyph (i.e. only the last loaded glyph is stored)
			if (ftError)
			{
				LOG_ERROR << "Error loading Glyph with index: " << uIndex;
				assert(false);
			}

			FT_Glyph_Format ftGF = ftFace->glyph->format;
			if (ftGF != FT_GLYPH_FORMAT_BITMAP) // Ok to convert to ftBitmap immediately
			{
				// Check FT_Render_Mode for available modes (anti-aliased, mono etc.)
				FT_Error ftError = FT_Render_Glyph(ftFace->glyph, FT_RENDER_MODE_NORMAL); // This renders the glyph into glyph->bitmap
				if (ftError)
				{
					LOG_ERROR << "Error rendering glyph bitmap";
					assert(false);
				}
			}
			LOG_ERROR << "Unsupported glyph format";
			assert(false);
		}

		boost::shared_ptr<Texture> createGlyphTexture(const FT_Bitmap& ftBitmap)
		{
			return null_ptr;
		}
	}

	boost::shared_ptr<Glyph> Font::getGlyph(unsigned char uChar) const
	{
		auto iter = m_GlyphMap.find(uChar);
		if (iter != m_GlyphMap.end())
		{
			LOG_VERBOSE << "Returning cached glyph: " << uChar;
			return iter->second;
		}

		LOG_VERBOSE << "Creating new glyph: " << uChar;

		createBitmap(m_FTFace, uChar);
		// Create texture from m_FTFace->glyph->bitmap
		// Render this texture into the atlas
		// Create Glyph object 

		// ??? Create new glyph here and render it into the atlas
		auto spGlyph = boost::shared_ptr<Glyph>(new Glyph(uChar, 0, 0, 0, 0, 0, Vec2(0.0f, 0.0f), Vec2(1.0, 1.0)));

		// Add to glyph cache
		m_GlyphMap[uChar] = spGlyph;
		return spGlyph;
	}

} }