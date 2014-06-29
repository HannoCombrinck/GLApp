#pragma once

#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem.hpp>

#include <Graphics/ShaderObject.h>
#include <Helpers/ResourceCache.h>

namespace fs = boost::filesystem;

namespace baselib 
{
	namespace graphics
	{
		/*! @brief ShaderLoader loads ShaderObjects.
		 *
		 */
		class ShaderLoader
		{
		public:
			//! Creates a ShaderLoader.
			static boost::shared_ptr<ShaderLoader> create();

			//! Destructor.
			virtual ~ShaderLoader();

			//! Load and creates a shader object from file. File extension determines shader type.
			boost::shared_ptr<ShaderObject> loadShaderObject(const fs::path& fsPath);

		protected:
			//! Protected constructor - must be created by static create().
			ShaderLoader();


		private:
			ResourceCache<ShaderObject> m_ShaderCache; //!< Shader object cache.

		};
	}
}