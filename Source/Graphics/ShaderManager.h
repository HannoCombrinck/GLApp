#pragma once

#include <string>
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
			//! Constructor
			ShaderManager();
			//! Destructor
			~ShaderManager();

			//! Creates, compiles and returns a shader object from file. File extension determines shader type.
			boost::shared_ptr<ShaderObject> createShaderObject(const fs::path& fsPath);
			//! Creates, compiles and returns a shader object from source.
			boost::shared_ptr<ShaderObject> createShaderObject(const std::string& sShaderSource, ShaderObject::ShaderType eType);

		private:
			//! Loads source code from a text file into sSource string.
			std::string loadSourceFromFile(const fs::path& fsPath);
			//! Gets the shader type from file extension.
			ShaderObject::ShaderType getShaderObjectType(const std::string& sExtension);

		};
	}
}