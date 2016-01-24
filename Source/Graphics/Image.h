﻿#pragma once

#include <memory>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

namespace baselib 
{
	namespace graphics
	{
		/*! @brief TODO
		 *
		 */
		class Image
		{
		public:
			//! Load an image from file
			static std::shared_ptr<Image> load(const fs::path& fsPath);

			//! Create an image object
			static std::shared_ptr<Image> create(int iWidth, int iHeight, int iBPP, unsigned char* pData);

			//! Destructor.
			virtual ~Image();

			//! Get image width.
			int getWidth() const { return m_iWidth; }
			//! Get image height.
			int getHeight() const { return m_iHeight; }
			//! Get image depth.
			int getBPP() const { return m_iBPP; }
			//! Get image data.
			unsigned char* getData() { return m_pData; }
		
		protected:
			//! Protected constructor - must be constructed by static Create().
			Image(int iWidth, int iHeight, int iBPP, unsigned char* pData);

		private:
			int m_iWidth;			//!< Width of the image.
			int m_iHeight;			//!< Height of the image.
			int m_iBPP;				//!< Bits per pixel.
			unsigned char* m_pData; //!< Raw image data.

		};
	}
}