﻿#pragma once

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
			friend class TextureFactory;

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
		
			//! Bind texture.
			void bind();
			//! Unbind texture.
			void unbind();

			//! Get the texture object ID.
			unsigned int getID() { return m_uID; }
			//! Get the texture type. TODO: This should be an abstract function and implementations should return appropriate type - just returning TEXTURE_2D now for testing
			//virtual TextureType getType() const = 0;
			virtual TextureType getType() const { return TEXTURE_2D; }

		protected:
			//! Protected constructor - must be constructed by TextureFactory.
			Texture(unsigned int uID, TextureType eType);

		private:
			unsigned int m_uID;  //!< Texture object ID.
			TextureType m_eType; //!< Texture type.

		};
	}
}