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
		/*! @brief Loads and creates fonts from file.
		 *
		 */
		class FontLoader
		{
		public:
			FontLoader();
			~FontLoader();
		
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