#pragma once

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
			friend class TextureManager;

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
			
			//! Destructor.
			virtual ~Texture();
		
			//! Get the texture object ID.
			unsigned int getID() { return m_uID; }
			//! Get the texture type.
			virtual TextureType getType() const = 0;

		protected:
			//! Protected constructor - must be constructed by TextureManager.
			Texture(unsigned int uID);

		private:
			unsigned int m_uID; //!< Texture object ID.

		};
	}
}