#include "ShaderManager.h"

#include <boost/filesystem/fstream.hpp>

#include <Logging/Log.h>

namespace baselib { namespace graphics {

	ShaderManager::ShaderManager()
	{
		LOG_VERBOSE << "ShaderManager constructor";
	}

	ShaderManager::~ShaderManager()
	{
		LOG_VERBOSE << "ShaderManager destructor";
	}
	
	boost::shared_ptr<ShaderObject> ShaderManager::CreateShaderObject(const fs::path& fsPath, ShaderObject::ShaderType eType)
	{
		return boost::shared_ptr<ShaderObject>();
	}

	boost::shared_ptr<ShaderObject> ShaderManager::CreateShaderObject(const std::string& sShaderSource, ShaderObject::ShaderType eType)
	{
		return boost::shared_ptr<ShaderObject>();
	}

	std::string ShaderManager::loadSourceFromFile(const fs::path& fsPath)
	{
		fs::ifstream inFile(fsPath);
		if (!inFile.is_open())
		{
			LOG_ERROR << "Failed to open file " << fsPath;
			assert(false);
		}

		std::string sSource;
		sSource.assign(std::istreambuf_iterator<char>(inFile), std::istreambuf_iterator<char>());

		inFile.close();

		return sSource;
	}

} }