#pragma once

#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem.hpp>

#include <Graphics/Texture.h>
#include <Helpers/ResourceCache.h>

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
		/*! @brief TextureFactory creates and caches textures.
		 *
		 */
		class TextureFactory
		{
		public:
			//! Constructor.
			TextureFactory();
			//! Destructor.
			virtual ~TextureFactory();

			//! Creates and returns a texture object from file.
			boost::shared_ptr<Texture> createTexture(const fs::path& fsPath);

			//! Creates and returns a texture from an image.
			boost::shared_ptr<Texture> createTexture(const boost::shared_ptr<Image>& spImage);

		private:
			ResourceCache<Texture> m_TextureCache; //!< Texture object cache.

		};
	}
}