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
		class ShaderPipeline;
	}
}

namespace baselib 
{
	namespace graphics
	{
		/*! @brief ShaderFactory creates and caches ShaderObjects and ShaderPipelines.
		 *
		 */
		class ShaderFactory
		{
		public:
			//! Constructor.
			ShaderFactory();
			//! Destructor.
			virtual ~ShaderFactory();

			//! Creates and links a shader pipeline with the given shader objects.
			boost::shared_ptr<ShaderPipeline> createShaderPipeline(const std::string& sName, const std::vector<boost::shared_ptr<ShaderObject>>& aspShaderObjects);
			//! Creates, compiles and returns a shader object from file. File extension determines shader type.
			boost::shared_ptr<ShaderObject> createShaderObject(const fs::path& fsPath);
			//! Creates, compiles and returns a shader object from source.
			boost::shared_ptr<ShaderObject> createShaderObject(const std::string& sShaderSource, ShaderObject::ShaderType eType);

		private:
			ResourceCache<ShaderObject> m_ShaderCache; //!< Shader object cache.

		};
	}
}