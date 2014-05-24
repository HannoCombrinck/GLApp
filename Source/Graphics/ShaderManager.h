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

			//! Creates, compiles and returns a shader object from file.
			boost::shared_ptr<ShaderObject> CreateShaderObject(const fs::path& fsPath, ShaderObject::ShaderType eType);
			//! Creates, compiles and returns a shader object from source.
			boost::shared_ptr<ShaderObject> CreateShaderObject(const std::string& sShaderSource, ShaderObject::ShaderType eType);

		private:
			//! Loads source code from a text file into sSource string.
			std::string loadSourceFromFile(const fs::path& fsPath);

		};
	}
}