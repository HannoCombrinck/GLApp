#pragma once

#include <boost/shared_ptr.hpp>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

namespace baselib 
{
	namespace graphics
	{
		class Image;
	}
}

namespace baselib 
{
	namespace graphics
	{
		/*! @brief TODO
		 *
		 */
		class Texture
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
			static boost::shared_ptr<Texture> load(const fs::path& fsPath);

			//! Creates and returns a texture from an image.
			static boost::shared_ptr<Texture> create(const boost::shared_ptr<Image>& spImage);
			
			//! Destructor.
			virtual ~Texture();
		
			//! Bind texture.
			void bind();

			//! Get the texture object ID.
			unsigned int getID() { return m_uID; }
			//! Get the texture type. TODO: This should be an abstract function and implementations should return appropriate type - just returning TEXTURE_2D now for testing
			//virtual TextureType getType() const = 0;
			virtual TextureType getType() const { return TEXTURE_2D; }
			//! Get texture width.
			int getWidth() const { return m_iWidth; }
			//! Get texture height.
			int getHeight() const { return m_iHeight; }
			//! Get texture depth.
			int getBPP() const { return m_iBPP; }

		protected:
			//! Protected constructor - must be constructed by static Create().
			Texture(unsigned int uID, TextureType eType, int iWidth, int iHeight, int iBPP);

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