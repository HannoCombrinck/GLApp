#pragma once

#include <boost/shared_ptr.hpp>
#include <boost/filesystem.hpp>
#include <Math/Math.h>

namespace fs = boost::filesystem;

namespace baselib
{
	namespace font
	{
		class Font;
	}
}

namespace baselib
{
	namespace font
	{
		/*! @brief Font factory wraps freetype library and creates fonts.
		 *
		 */
		class FontFactory
		{
		public:
			FontFactory();
			~FontFactory();
		
			//! Create a font.
			boost::shared_ptr<Font> createFont(const fs::path& fsPath, const Vec2& vAtlasSize);
		
		private:
			//! Initialize freetype library.
			void init();
			//! Destroy the freetype library.
			void destroy();
		
		};
	}
}