#pragma once

#include <string>
#include <boost/filesystem.hpp>

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

		private:
		
		};
	}
}