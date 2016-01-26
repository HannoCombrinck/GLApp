#pragma once

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
		class TextureGLI
		{
		public:
			//! All possible texture types.
			enum TextureType
			{
				TEXTURE_1D,
				TEXTURE_2D,
				TEXTURE_3D,
				TEXTURE_RECTANGLE,
				TEXTURE_BUFFER,
				TEXTURE_CUBE_MAP,
				TEXTURE_1D_ARRAY,
				TEXTURE_2D_ARRAY,
				TEXTURE_CUBE_MAP_ARRAY,
				TEXTURE_2D_MULTISAMPLE
			};

			//! Loads a texture object from file.
			static std::shared_ptr<TextureGLI> load(const fs::path& fsPath);

			//! Creates and returns a texture from an image.
			//static std::shared_ptr<TextureGLI> create();
			
			//! Destructor.
			virtual ~TextureGLI();
		
			//! Bind texture.
			void bind(unsigned int uUnit = 0);

			//! Get the texture object ID.
			unsigned int getID() { return m_uID; }
			//! Get the texture type.
			virtual TextureType getType() const { return TEXTURE_2D; }
			
			//! Get texture width.
			int getWidth() const { return m_iWidth; }
			//! Get texture height.
			int getHeight() const { return m_iHeight; }
			//! Get texture depth.
			int getBPP() const { return m_iBPP; }

		protected:
			//! Protected constructor - must be constructed by static Create().
			TextureGLI(unsigned int uID, TextureType eType, int iWidth, int iHeight, int iBPP);

		private:
			static unsigned int m_uCurrentlyBound; //!< Currently bound texture.
			static unsigned int m_uActiveUnit;	   //!< Active texture unit.

			unsigned int m_uID;  //!< Texture object ID.
			TextureType m_eType; //!< Texture type.
			int m_iWidth;		 //!< Texture width.
			int m_iHeight;		 //!< Texture height.
			int m_iBPP;			 //!< Texture bits per pixel.

		};
	}
}