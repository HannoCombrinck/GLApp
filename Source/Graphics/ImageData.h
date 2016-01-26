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
		/*! @brief ImageData represents a 2D block of pixels stored in the given format
		 *
		 */
		class ImageData : public Resource
		{
		public:

			//! Pixel data format
			enum PixelFormat
			{
				G8,			// Grayscale - 8 bits per pixel
				G16F,		// Grayscale - 16 bits per pixel, floating point format
				G32F,		// Grayscale - 32 bits per pixel, floating point format 
				RGB8,		// RGB - 8 bits per channel, 24 bits per pixel
				RGBA8,		// RGBA - 8 bits per channel, 32 bits per pixel
				RGBA16F,	// RGBA - 16 bits per channel, 64 bits per pixel, floating point format
				RGBA32F,	// RGBA - 32 bits per channel, 128 bits per pixel, floating point format
				DXT1,		// RGB - hardware compression, 6:1 ratio no alpha
				DXT3,		// RGBA - hardware compression, 4:1 ratio with explicit alpha
				DXT5,		// RGBA - hardware compression, 4:1 ratio with interpolated alpha
				UNDEFINED	// Undefined format
			};
	
			//! Load image data from file
			static std::shared_ptr<ImageData> load(const fs::path& fsPath);

			//! Create an image object
			static std::shared_ptr<ImageData> create(unsigned int uWidth, unsigned int uHeight, PixelFormat eFormat, unsigned char* pData);

			//! Destructor.
			virtual ~ImageData();

			//! Get image width.
			unsigned int getWidth() const { return m_uWidth; }
			//! Get image height.
			unsigned int getHeight() const { return m_uHeight; }
			//! Get image depth.
			PixelFormat getFormat() const { return m_eFormat; }
			//! Get image data.
			unsigned char* getData() { return m_pData; }

			//! Resource type override
			virtual std::string getResourceType() const { return "ImageData"; }
		
		protected:
			//! Protected constructor - must be constructed by static Create().
			ImageData(unsigned int uWidth, unsigned int uHeight, PixelFormat eFormat, unsigned char* pData);

		private:
			unsigned int m_uWidth;	//!< Width of the image.
			unsigned int m_uHeight;	//!< Height of the image.
			PixelFormat m_eFormat;	//!< Pixel format.
			unsigned char* m_pData; //!< Raw image data.

		};
	}
}