#include "Font.h"

#include <Core/NullPtr.h>
#include <Graphics/Renderer.h>
#include <Graphics/Texture.h>
#include <Graphics/Image.h>
#include <Graphics/ShaderObject.h>
#include <Graphics/ShaderPipeline.h>
#include <Graphics/Shader.h>
#include <Graphics/Helpers/TextureUpdateHelper.h>
#include <Logging/Log.h>
#include <Font/Glyph.h>
#include <ft2build.h>
#include FT_FREETYPE_H

using namespace baselib::graphics;

namespace baselib { namespace font {

	Font::Font(FT_FaceRec_ *ftFace, const std::shared_ptr<Renderer>& spRenderer, const Vec2& vAtlasSize)
		: m_FTFace(ftFace)
		, m_spRenderer(spRenderer)
		, m_vNextGlyphBottomLeft(Vec2(0.0f, 0.0f))
		, m_fMaxHeight(0.0f)
	{
		LOG_VERBOSE << "Font constructor";
		init(vAtlasSize);

		/*
		// Kerning
		bool bHasKerning = false;
		if (FT_HAS_KERNING(m_FTFace))
			bHasKerning = true;

		FT_Vector ftKerning;
		unsigned int uIndexLeft = 0;
		unsigned int uIndexRight = 1;
		// When uIndexLeft is 0 then the kerning is always 0
		FT_Get_Kerning(m_FTFace, uIndexLeft, uIndexRight, FT_KERNING_DEFAULT, &ftKerning);  // FT_KERNING_DEFAULT - kerning is in units of 1/64th of a pixel width
		*/
	}

	Font::~Font()
	{
		LOG_VERBOSE << "Font destructor";
	}

	void Font::init(const Vec2& vAtlasSize)
	{
		auto spImage = Image::create(int(vAtlasSize.x), int(vAtlasSize.y), 8, 0);
		m_spAtlas = Texture::create(spImage);
		m_spTextureUpdateHelper = TextureUpdateHelper::create(m_spRenderer);

		std::vector<std::shared_ptr<ShaderObject>> aShaderObjects;
		aShaderObjects.push_back(ShaderObject::load("../Data/Shaders/TextureCopy.vert"));
		aShaderObjects.push_back(ShaderObject::load("../Data/Shaders/TextureCopy.frag"));
		m_spTextureCopyPipeline = ShaderPipeline::create("TextureCopy", aShaderObjects);
		m_spTextureCopyShader = m_spTextureCopyPipeline->createInstance();
	}

	namespace
	{
		// Render the bitmap for uChar and store in FT_Face slot i.e. bitmap data for uChar is rendered to m_FTFace->glyph->bitmap
		void fillBitmap(FT_Face ftFace, unsigned char uChar)
		{
			FT_UInt uIndex = FT_Get_Char_Index(ftFace, uChar);
			if (uIndex == 0)
			{
				LOG_ERROR << "Glyph not found for character: " << uChar;
				assert(false);
			}

			int iFlags = FT_LOAD_DEFAULT;
			FT_Error ftError = FT_Load_Glyph(ftFace, uIndex, iFlags); // This loads the glyph into ftFace->glyph (i.e. only the last loaded glyph is stored)
			if (ftError)
			{
				LOG_ERROR << "Error loading Glyph with index: " << uIndex;
				assert(false);
			}

			//FT_Glyph_Format ftGF = ftFace->glyph->format;

			// Check FT_Render_Mode for available modes (anti-aliased, mono etc.)
			ftError = FT_Render_Glyph(ftFace->glyph, FT_RENDER_MODE_NORMAL); // This renders the glyph into glyph->bitmap
			if (ftError)
			{
				LOG_ERROR << "Error rendering glyph bitmap";
				assert(false);
			}
		}

		// Create a texture from a FT_Bitmap
		std::shared_ptr<Texture> createGlyphTexture(const FT_Bitmap& ftBitmap)
		{
			int iWidth = ftBitmap.width;
			int iHeight = ftBitmap.rows;
			unsigned char *pData = new unsigned char[iWidth * iHeight]; // 1 byte per pixel

			for (int y = 0; y < iHeight; ++y)
			{
				for (int x = 0; x < iWidth; ++x)
				{
					pData[y*iWidth + x] = ftBitmap.buffer[(iHeight - y - 1)*iWidth + x];
				}
			}

			auto spImage = Image::create(iWidth, iHeight, 8, pData);
			return Texture::create(spImage);
		}

	}

	std::shared_ptr<Glyph> Font::getGlyph(unsigned char uChar) const
	{
		auto iter = m_GlyphMap.find(uChar);
		if (iter != m_GlyphMap.end())
		{
			LOG_VERBOSE << "Returning cached glyph: " << uChar;
			return iter->second;
		}

		LOG_VERBOSE << "Creating new glyph: " << uChar;

		// Render bitmap
		fillBitmap(m_FTFace, uChar);

		// Create texture from bitmap
		FT_Bitmap& ftBitmap = m_FTFace->glyph->bitmap;
		auto spGlyphTexture = createGlyphTexture(ftBitmap);
		m_spTextTex = spGlyphTexture;

		// Render this texture into the atlas
		Vec2 vUVMin(0.0f, 0.0f);
		Vec2 vUVMax(1.0f, 1.0f);
		if (!addToAtlas(m_vNextGlyphBottomLeft, m_fMaxHeight, vUVMin, vUVMax, spGlyphTexture, m_spAtlas))
		{
			LOG_ERROR << "Font atlas is full";
			assert(false);
		}
		
		// Create glyph
		FT_Glyph_Metrics ftGM = m_FTFace->glyph->metrics;
		// All metrics measured in 1/64th of a pixel i.e. iWidth * 64 = width in pixels - unless FT_LOAD_NO_SCALE is used (check freetype docs)
		unsigned int uWidth = unsigned int(ftGM.width) * 64;
		unsigned int uHeight = unsigned int(ftGM.height) * 64;
		unsigned int uAdvance = unsigned int(ftGM.horiAdvance) * 64;
		unsigned int uBearingX = unsigned int(ftGM.horiBearingX) * 64;
		unsigned int uBearingY = unsigned int(ftGM.horiBearingY) * 64;
		auto spGlyph = std::shared_ptr<Glyph>(new Glyph(uChar, uWidth, uHeight, uAdvance, uBearingX, uBearingY, vUVMin, vUVMax));

		// Add to glyph cache
		m_GlyphMap[uChar] = spGlyph;
		return spGlyph;
	}

	bool Font::addToAtlas(Vec2& vNextGlyphBottomLeft, float& fMaxHeight, Vec2& vUVMin, Vec2& vUVMax, const std::shared_ptr<Texture>& spTexture, const std::shared_ptr<Texture>& spAtlas) const
	{
		// Check if glyph will fit horizontally
		if (vNextGlyphBottomLeft.x + spTexture->getWidth() > spAtlas->getWidth())
			vNextGlyphBottomLeft = Vec2(0.0f, fMaxHeight);

		// Check max height for this row of glyphs 
		if (vNextGlyphBottomLeft.y + spTexture->getHeight() > fMaxHeight)
			fMaxHeight = vNextGlyphBottomLeft.y + spTexture->getHeight();

		// Get UV coordinates of next open spot in the atlas
		vUVMin = Vec2(vNextGlyphBottomLeft.x / spAtlas->getWidth(), vNextGlyphBottomLeft.y / spAtlas->getHeight());
		vUVMax = Vec2((vNextGlyphBottomLeft.x + spTexture->getWidth()) / spAtlas->getWidth(), (vNextGlyphBottomLeft.y + spTexture->getHeight()) / spAtlas->getHeight());

		// Set next horizontal available position
		vNextGlyphBottomLeft.x += spTexture->getWidth();

		// Check if glyph will fit in atlas
		if (vUVMax.x > 1.0 || vUVMax.y > 1.0)
			return false;

		// Render glyph into atlas
		m_spTextureUpdateHelper->updateRegion(spTexture, vUVMin, vUVMax, spAtlas, m_spTextureCopyShader);

		return true;
	}

} }