#pragma once

#include <memory>
#include <boost/filesystem.hpp>

#include <Core/Resource.h>

//TEMP
#include <gli/texture.hpp>
#include <gli/gl.hpp>
//

namespace fs = boost::filesystem;

namespace baselib 
{
	namespace graphics
	{
		/*! @brief TODO
		 *
		 */
		class ImageData : public Resource
		{
		public:

			enum ImageFormat
			{
				G8,
				G16,
				G32,
				RGB8,
				RGBA8,
				RGBA16F,
				RGBA32F,
				DXT1,
				DXT3,
				DXT5,
				UNDEFINED
			};
	
			//! Load image data from file
			static std::shared_ptr<ImageData> load(const fs::path& fsPath);

			//! Create an image object
			static std::shared_ptr<ImageData> create(int iWidth, int iHeight, ImageFormat eFormat, unsigned char* pData);

			//! Destructor.
			virtual ~ImageData();

			//! Get image width.
			int getWidth() const { return m_iWidth; }
			//! Get image height.
			int getHeight() const { return m_iHeight; }
			//! Get image depth.
			ImageFormat getFormat() const { return m_eFormat; }
			//! Get image data.
			unsigned char* getData() { return m_pData; }
		
		protected:
			//! Protected constructor - must be constructed by static Create().
			ImageData(int iWidth, int iHeight, ImageFormat eFormat, unsigned char* pData);

		private:
			int m_iWidth;			//!< Width of the image.
			int m_iHeight;			//!< Height of the image.
			ImageFormat m_eFormat;			//!< Pixel format.
			unsigned char* m_pData; //!< Raw image data.

		};
	}
}