#pragma once

#include <string>
#include <boost/unordered_map.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem.hpp>

#include <Graphics/ShaderObject.h>

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
		/*! @brief ShaderManager creates and managers ShaderObjects and ShaderPipelines.
		 *
		 */
		class ShaderManager
		{
		public:
			//! Constructor.
			ShaderManager();
			//! Destructor.
			~ShaderManager();

			//! Creates and links a shader pipeline with the given shader objects.
			boost::shared_ptr<ShaderPipeline> createShaderPipeline(const std::string& sName, const std::vector<boost::shared_ptr<ShaderObject>>& aspShaderObjects);

			//! Creates, compiles and returns a shader object from file. File extension determines shader type.
			boost::shared_ptr<ShaderObject> createShaderObject(const fs::path& fsPath);
			//! Creates, compiles and returns a shader object from source.
			boost::shared_ptr<ShaderObject> createShaderObject(const std::string& sShaderSource, unsigned int uType);

		private:
			boost::unordered_map<std::string, boost::weak_ptr<ShaderObject>> m_aShaderObjectMap; //!< Map with weak references to all created ShaderObjects.
		
		};
	}
}