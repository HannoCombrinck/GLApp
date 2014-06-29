#pragma once

#include <Math/Math.h>
#include <boost/shared_ptr.hpp>
#include <boost/unordered_map.hpp>

struct FT_FaceRec_;

namespace baselib
{
	namespace font
	{
		class Glyph;
	}

	namespace graphics
	{
		class Texture;
	}
}

namespace baselib
{
	namespace font
	{
		/*! @brief Font encapsulates a font face i.e. contains information about every glyph/symbol/character in the font.
		 *
		 *  Font has a atlas texture which is updated on demand. When a new glyph is requested it is rendered into
		 *  the font atlas and its texture coordinates are stored.
		 */
		class Font
		{
		public:
			friend class FontLoader;

			//! Destructor.
			~Font();
		
			//! Get the glyph for a character.
			boost::shared_ptr<Glyph> getGlyph(unsigned char uChar) const;

			//! Get the texture atlas.
			boost::shared_ptr<graphics::Texture> getAtlas() const { return m_spAtlas; }

			//! Temp get test tex
			boost::shared_ptr<graphics::Texture> getTestTex() const { return m_spTextTex; }

		protected:
			//! Protected constructor - must be created by FontLoader.
			Font(FT_FaceRec_ *ftFace, const Vec2& vAtlasSize);

		private:
			//! Initialize the Font and create texture atlas.
			void init(const Vec2& vAtlasSize);

			FT_FaceRec_ *m_FTFace;															  //!< Freetype face pointer.
			mutable boost::unordered_map<unsigned char, boost::shared_ptr<Glyph>> m_GlyphMap; //!< Glyph cache.
			boost::shared_ptr<graphics::Texture> m_spAtlas;									  //!< Texture atlas containing cached glyphs for this font.
			mutable Vec2 m_vNextGlyphBottomLeft;											  //!< The next avaiable position in the texture atlas. The next requested glyph's bottom left corner will be placed here.
			mutable float m_fMaxHeight;														  //!< The height at which to start the next row of glyphs in the atlas.

			mutable boost::shared_ptr<graphics::Texture> m_spTextTex;
		};
	}
}