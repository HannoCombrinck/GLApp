#pragma once

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
			friend class ImageLoader;

			//! Destructor.
			virtual ~Image();
		
		protected:
			//! Protected constructor - must be constructed by ImageLoader.
			Image(int iWidth, int iHeight, int iBPP, unsigned char* pData);

		private:
			int m_iWidth;			//!< Width of the image.
			int m_iHeight;			//!< Height of the image.
			int m_iBPP;				//!< Bits per pixel.
			unsigned char* m_pData; //!< Raw image data.

		};
	}
}