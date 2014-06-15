#pragma once

#include <string>
#include <boost/unordered_map.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/filesystem.hpp>

#include <Graphics/Texture.h>

namespace fs = boost::filesystem;

namespace baselib 
{
	namespace graphics
	{
		/*! @brief TextureManager creates and manages textures.
		 *
		 */
		class TextureManager
		{
		public:
			//! Constructor.
			TextureManager();
			//! Destructor.
			virtual ~TextureManager();

			//! Creates and returns a texture object from file.
			boost::shared_ptr<Texture> createTexture(const fs::path& fsPath);
			//! Creates and returns a texture from image data.
			//boost::shared_ptr<Texture> createTexture();

		private:
			boost::unordered_map<std::string, boost::weak_ptr<Texture>> m_aTextureMap; //!< Map with weak references to all created textures.
		
		};
	}
}