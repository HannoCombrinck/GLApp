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
		/*! @brief ImageLoader wraps GLI and supports loading of several image formats.
		 *
		 */
		class ImageLoader
		{
		public:
			//! Constructor.
			ImageLoader();
			//! Destructor.
			virtual ~ImageLoader();

			//! Load an image from file
			boost::shared_ptr<Image> loadImage(const fs::path& fsPath);

		private:
			ResourceCache<Image> m_ImageCache;
		
		};
	}
}