#pragma once

#include <memory>
#include <vector>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

namespace baselib 
{
	namespace graphics
	{
		class ImageData;
	}
}

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
			virtual TextureType getType() const { return TEXTURE_2D; } // TODO

			//! Get the number of array slices
			unsigned int getNumArraySlices() const { return m_uArraySlices; }
			//! Get the number of texture faces
			unsigned int getNumFaces() const { return m_uFaces; }
			//! Get the number of mipmap levels
			unsigned int getNumMipMaps() const { return m_uMipLevels; }
			

		protected:
			//! Protected constructor - must be constructed by static Create().
			TextureGLI(unsigned int uID, TextureType eType);

		private:
			static unsigned int m_uCurrentlyBound; //!< Currently bound texture.
			static unsigned int m_uActiveUnit;	   //!< Active texture unit.

			unsigned int m_uID;				//!< Texture object ID.
			TextureType m_eType;			//!< Texture type.
			unsigned int m_uArraySlices;	//!< Number of slices in texture array.
			unsigned int m_uFaces;			//!< Number of faces, for the sake of cubemaps.
			unsigned int m_uMipLevels;		//!< Number of mipmap levels.

			//! Texture images for all array slices, cube faces and mipmap levels
			std::vector<std::vector<std::vector<std::shared_ptr<ImageData>>>> m_Images;
		};
	}
}