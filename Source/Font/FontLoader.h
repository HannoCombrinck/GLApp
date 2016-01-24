#pragma once

#include <memory>
#include <boost/filesystem.hpp>
#include <Math/Math.h>

namespace fs = boost::filesystem;

namespace baselib
{
	namespace font
	{
		class Font;
	}
	namespace graphics
	{
		class Renderer;
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
			static std::shared_ptr<FontLoader> create();
			
			//! Destructor.
			~FontLoader();
		
			//! Load and create a font.
			std::shared_ptr<Font> loadFont(const fs::path& fsPath, const std::shared_ptr<graphics::Renderer>& spRenderer, const Vec2& vAtlasSize);

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