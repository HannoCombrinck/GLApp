#include "ShaderObject.h"

#include <GL/glew.h>
#include <Logging/Log.h>
#include <Helpers/ResourceCache.h>
#include <boost/filesystem/fstream.hpp>
#include <boost/range/algorithm/for_each.hpp>
#include <boost/unordered_map.hpp>
#include <boost/assign/list_of.hpp>

namespace baselib { namespace graphics {

	namespace
	{
		ResourceCache<ShaderObject> m_ShaderCache;

		boost::unordered_map<ShaderObject::ShaderType, std::pair<std::string, unsigned int>> aShaderTypeMap = boost::assign::map_list_of
			(ShaderObject::VERTEX_SHADER,		   std::make_pair("vertex",					 GL_VERTEX_SHADER))
			(ShaderObject::TESS_CONTROL_SHADER,    std::make_pair("tessellation control",	 GL_TESS_CONTROL_SHADER))
			(ShaderObject::TESS_EVALUATION_SHADER, std::make_pair("tessellation evaluation", GL_TESS_EVALUATION_SHADER))
			(ShaderObject::GEOMETRY_SHADER,		   std::make_pair("geometry",				 GL_GEOMETRY_SHADER))
			(ShaderObject::FRAGMENT_SHADER,		   std::make_pair("fragment",				 GL_FRAGMENT_SHADER))
			(ShaderObject::COMPUTE_SHADER,		   std::make_pair("compute",				 GL_COMPUTE_SHADER))
			;

		boost::unordered_map<std::string, ShaderObject::ShaderType> aShaderExtensionMap  = boost::assign::map_list_of
			(".vert", ShaderObject::VERTEX_SHADER)
			(".tesc", ShaderObject::TESS_CONTROL_SHADER)
			(".tese", ShaderObject::TESS_EVALUATION_SHADER)
			(".geom", ShaderObject::GEOMETRY_SHADER)
			(".frag", ShaderObject::FRAGMENT_SHADER)
			(".comp", ShaderObject::COMPUTE_SHADER)
			;

		ShaderObject::ShaderType getTypeFromExtension(const std::string& sExtension) { return aShaderExtensionMap[sExtension]; }
		unsigned int getGLShaderType(ShaderObject::ShaderType eType) { return aShaderTypeMap[eType].second;	}
		std::string getShaderTypeString(ShaderObject::ShaderType eType) { return aShaderTypeMap[eType].first; }

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

	boost::shared_ptr<ShaderObject> ShaderObject::load(const fs::path& fsPath)
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

	boost::shared_ptr<ShaderObject> ShaderObject::create(const std::string& sShaderSource, ShaderType eType)
	{
		// Get GL shader type
		unsigned int uGLShaderType = getGLShaderType(eType);

		// Get shader type as a string
		std::string sShaderType = getShaderTypeString(eType);

		// Create the shader
		LOG_VERBOSE << "Creating " << sShaderType << " shader";
		unsigned int uShaderObjectID = glCreateShader(uGLShaderType);
		assert(uShaderObjectID);

		// Commit the shader source to compiler
		const char* szShaderSource = sShaderSource.c_str();
		glShaderSource(uShaderObjectID, 1, (const char**)&szShaderSource, NULL);

		// Compile the shader
		LOG_INFO << "Compiling " << sShaderType << " shader";
		glCompileShader(uShaderObjectID);

		// Get GLSL compiler status
		int iCompileStatus = 0;
		glGetShaderiv(uShaderObjectID, GL_COMPILE_STATUS, &iCompileStatus);
		if (iCompileStatus == GL_TRUE)
		{
			LOG_VERBOSE << "Successfully compiled " << sShaderType << " shader";
		}
		else
		{
			LOG_ERROR << "Failed to compile " << sShaderType << " shader";
			glDeleteShader(uShaderObjectID);
			uShaderObjectID = ~0;
			// Assert after logging GLSL compiler errors
		}

		// Get GLSL compiler log
		int iLogLength = 0;
		glGetShaderiv(uShaderObjectID, GL_INFO_LOG_LENGTH, &iLogLength);
		char *szLog = new char[iLogLength + 1];
		glGetShaderInfoLog(uShaderObjectID, iLogLength, NULL, szLog);
		std::string sCompilerLog(szLog);
		delete[] szLog;

		if (!sCompilerLog.empty())
			LOG_INFO << sCompilerLog;

		assert(iCompileStatus == GL_TRUE);

		return boost::shared_ptr<ShaderObject>(new ShaderObject("", eType, uShaderObjectID, sShaderSource));;
	}

	ShaderObject::ShaderObject(const std::string& sName, ShaderType eType, unsigned int iID, const std::string& sSource) : m_sName(sName)
		, m_eType(eType)
		, m_uID(iID)
		, m_sSource(sSource)
	{
		LOG_VERBOSE << "ShaderObject constructor";
	}

	ShaderObject::~ShaderObject()
	{
		LOG_VERBOSE << "ShaderObject destructor";
		glDeleteShader(m_uID);
	}

} }