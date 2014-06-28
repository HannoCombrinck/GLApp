#pragma once

#include <Math/Math.h>

namespace baselib
{
	namespace font
	{
		/*! @brief A Glyph represents a single character.
		 *
		 */
		class Glyph
		{
		public:
			friend class Font;

			//! Destructor.
			~Glyph();
		
		protected:
			//! Protected constructor - must be created by Font.
			Glyph(unsigned char uChar, unsigned int uWidth, unsigned int uHeight, unsigned int uAdvance, unsigned int uBearingX, unsigned int uBearingY, const Vec2& vUVMin, const Vec2& vUVMax);
		
		private:
			unsigned char m_uChar;	  //!< The character represented by this glyph.
			unsigned int m_uWidth;    //!< Glyph bitmap width in pixels.
			unsigned int m_uHeight;   //!< Glyph bitmap height in pixels.
			unsigned int m_uAdvance;  //!< The width this character takes up on the baseline (in pixels) without kerning.
			unsigned int m_uBearingX; //!< The horizontal bearing - distance from cursor to left border of glyph.
			unsigned int m_uBearingY; //!< The vertical bearing - distance from baseline to top border of glyph.
			Vec2 m_vUVMin;			  //!< The glyph's bottom left UV coordinates in the font atlas texture.
			Vec2 m_vUVMax;			  //!< The glyph's top right UV coordinates in the font atlas texture.

		};
	}
}