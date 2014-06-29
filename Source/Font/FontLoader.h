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
			//! Creates a FontLoader.
			static boost::shared_ptr<FontLoader> create();
			
			//! Destructor.
			~FontLoader();
		
			//! Load and create a font.
			boost::shared_ptr<Font> loadFont(const fs::path& fsPath, const Vec2& vAtlasSize);

		protected:
			//! Protected constructor - must be created by static create().
			FontLoader();

		private:
			//! Initialize freetype library.
			void init();
			//! Destroy the freetype library.
			void destroy();
		
		};
	}
}