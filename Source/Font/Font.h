#pragma once

#include <Math/Math.h>
#include <memory>
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
		class Renderer;
		class Shader;
		class ShaderPipeline;
		class Texture;
		class TextureUpdateHelper;
	}
}

namespace baselib
{
	namespace font
	{
		/*! @brief Font encapsulates a font face i.e. contains information about every glyph/symbol/character in the font.
		 *
		 *  Font has an atlas texture which is updated on demand. When a new glyph is requested it is rendered into
		 *  the font atlas and its texture coordinates are stored.
		 */
		class Font
		{
		public:
			friend class FontLoader;

			//! Destructor.
			~Font();
		
			//! Get the glyph for a character.
			std::shared_ptr<Glyph> getGlyph(unsigned char uChar) const;

			//! Get the texture atlas.
			std::shared_ptr<graphics::Texture> getAtlas() const { return m_spAtlas; }

		protected:
			//! Protected constructor - must be created by FontLoader.
			Font(FT_FaceRec_ *ftFace, const std::shared_ptr<graphics::Renderer>& spRenderer, const Vec2& vAtlasSize);

		private:
			//! Initialize the Font and create texture atlas.
			void init(const Vec2& vAtlasSize);
			//! Add a texture to the atlas and calculate the UV coordinates
			bool addToAtlas(Vec2& vNextGlyphBottomLeft, float& fMaxHeight, Vec2& vUVMin, Vec2& vUVMax, const std::shared_ptr<graphics::Texture>& spTexture, const std::shared_ptr<graphics::Texture>& spAtlas) const;

			FT_FaceRec_ *m_FTFace;															  //!< Freetype face pointer.
			std::shared_ptr<graphics::Renderer> m_spRenderer;								  //!< Renderer used to render into font atlas.
			std::shared_ptr<graphics::TextureUpdateHelper> m_spTextureUpdateHelper;		  //!< Helper to render glyphs into atlas.
			std::shared_ptr<graphics::ShaderPipeline> m_spTextureCopyPipeline;			  //!< Shader pipeline used to copy glyp texture into atlas.
			std::shared_ptr<graphics::Shader> m_spTextureCopyShader;						  //!< Shader instance used to copy glyph texture into atlas.
			std::shared_ptr<graphics::Texture> m_spAtlas;									  //!< Texture atlas containing cached glyphs for this font.
			mutable boost::unordered_map<unsigned char, std::shared_ptr<Glyph>> m_GlyphMap; //!< Glyph cache.
			mutable Vec2 m_vNextGlyphBottomLeft;											  //!< The next avaiable position in the texture atlas. The next requested glyph's bottom left corner will be placed here.
			mutable float m_fMaxHeight;														  //!< The height at which to start the next row of glyphs in the atlas.

			mutable std::shared_ptr<graphics::Texture> m_spTextTex;
		};
	}
}