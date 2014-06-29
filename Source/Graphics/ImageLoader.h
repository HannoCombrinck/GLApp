#pragma once

#include <string>
#include <boost/filesystem.hpp>

#include <Graphics/Image.h>
#include <Helpers/ResourceCache.h>

namespace fs = boost::filesystem;

namespace baselib 
{
	namespace graphics
	{
		/*! @brief ImageLoader
		 *
		 */
		class ImageLoader
		{
		public:
			//! Creates an ImageLoader.
			static boost::shared_ptr<ImageLoader> create();

			//! Destructor.
			virtual ~ImageLoader();

			//! Load an image from file
			boost::shared_ptr<Image> loadImage(const fs::path& fsPath);

		protected:
			//! Protected constructor - must be created by static create().
			ImageLoader();

		private:
			ResourceCache<Image> m_ImageCache;
		
		};
	}
}