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
		class ShaderManager
		{
		public:
			//! Constructor.
			ShaderManager();
			//! Destructor.
			~ShaderManager();

			// TODO: Create shader (i.e. shader program)

			//! Creates, compiles and returns a shader object from file. File extension determines shader type.
			boost::shared_ptr<ShaderObject> createShaderObject(const fs::path& fsPath);
			//! Creates, compiles and returns a shader object from source.
			boost::shared_ptr<ShaderObject> createShaderObject(const std::string& sShaderSource, ShaderObject::ShaderType eType);

		private:
			boost::unordered_map<std::string, boost::weak_ptr<ShaderObject>> m_aShaderObjectMap; //!< Map with weak references to all created ShaderObjects.

		};
	}
}