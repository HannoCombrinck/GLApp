#include "ShaderLoader.h"

#include <GL/glew.h>
#include <boost/filesystem/fstream.hpp>
#include <boost/range/algorithm/for_each.hpp>
#include <boost/assign/list_of.hpp>
#include <Logging/Log.h>

namespace baselib { namespace graphics {

	boost::shared_ptr<ShaderLoader> ShaderLoader::create()
	{
		return boost::shared_ptr<ShaderLoader>(new ShaderLoader());
	}

	ShaderLoader::ShaderLoader()
	{
		LOG_VERBOSE << "ShaderLoader constructor";
	}

	ShaderLoader::~ShaderLoader()
	{
		LOG_VERBOSE << "ShaderLoader destructor";
	}

	namespace
	{
		boost::unordered_map<std::string, ShaderObject::ShaderType> aShaderExtensionMap  = boost::assign::map_list_of
			(".vert", ShaderObject::VERTEX_SHADER)
			(".tesc", ShaderObject::TESS_CONTROL_SHADER)
			(".tese", ShaderObject::TESS_EVALUATION_SHADER)
			(".geom", ShaderObject::GEOMETRY_SHADER)
			(".frag", ShaderObject::FRAGMENT_SHADER)
			(".comp", ShaderObject::COMPUTE_SHADER)
			;

		ShaderObject::ShaderType getTypeFromExtension(const std::string& sExtension) { return aShaderExtensionMap[sExtension]; }

		// Loads source code from a text file into sSource string.
		std::string loadSourceFromFile(const fs::path& fsPath)
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
	}

	boost::shared_ptr<ShaderObject> ShaderLoader::loadShaderObject(const fs::path& fsPath)
	{
		// Check if file exists
		if (!fs::exists(fsPath))
		{
			LOG_ERROR << "Cannot find shader source file " << fsPath;
			assert(false);
		}

		// Get canonical path
		std::string sCanonicalPath = fs::canonical(fsPath).string();

		// Check shader cache
		if (auto sp = m_ShaderCache.get(sCanonicalPath))
			return sp;

		// Check if file has an extension
		if (!fsPath.has_extension())
		{
			LOG_ERROR << "Shader source file " << sCanonicalPath << " does not have an extension";
			assert(false);
		}
		
		// Get shader type from extension
		std::string sExtension = fsPath.extension().string();
		auto eType = getTypeFromExtension(sExtension);
		
		// Check for valid type
		if (eType == ShaderObject::INVALID_SHADER)
		{
			LOG_ERROR << "Invalid shader source file extension: " << sExtension << "\nValid extensions are:\n.vert\n.tesc\n.tese\n.geom\n.frag\n.comp";
			assert(false);
		}

		// Load the shader source from file and create the shader object
		LOG_INFO << "Loading: " << sCanonicalPath;
		std::string sSource = loadSourceFromFile(sCanonicalPath);
		auto spShaderObject = ShaderObject::create(sSource, eType);
		spShaderObject->setName(fsPath.string());

		// Cache the shader object
		m_ShaderCache.add(sCanonicalPath, spShaderObject);

		return spShaderObject;
	}

} }