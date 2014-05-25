#pragma once

#include <string>
#include <boost/unordered_map.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/filesystem.hpp>

#include <Graphics/ShaderObject.h>

namespace fs = boost::filesystem;

namespace baselib 
{
	namespace graphics
	{
		class ShaderManager : public boost::enable_shared_from_this<ShaderManager>
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
			//! Destroys the shader object.
			void destroyShaderObject(unsigned int uShaderObjectID);

		private:
			//! Loads source code from a text file into sSource string.
			std::string loadSourceFromFile(const fs::path& fsPath);
			//! Get shader type from the file extension.
			ShaderObject::ShaderType getTypeFromExtension(const std::string& sExtension);

			boost::unordered_map<std::string, boost::weak_ptr<ShaderObject>> m_aShaderObjectMap; //!< Map with weak references to all created ShaderObjects.

		};
	}
}