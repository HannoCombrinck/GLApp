#include "ShaderManager.h"

#include <GL/glew.h>

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
	
	boost::shared_ptr<ShaderObject> ShaderManager::createShaderObject(const fs::path& fsPath)
	{
		// Check if file exists
		if (!fs::exists(fsPath))
		{
			LOG_ERROR << "Cannot find shader source file " << fsPath;
			assert(false);
		}

		// Check if file has extension
		if (!fsPath.has_extension())
		{
			LOG_ERROR << "Shader source file " << fsPath << " does not have an extension.";
			assert(false);
		}
		
		// Get shader type from extension
		std::string sExtension = fsPath.extension().string();
		auto eType = getShaderObjectType(sExtension);
		
		// Check for valid extension
		if (eType == ShaderObject::INVALID_SHADER)
		{
			LOG_ERROR << "Invalid shader source file extension: " << sExtension << "\nValid extensions are:\n.vert\n.tesc\n.tese\n.geom\n.frag\n.comp";
			assert(false);
		}

		// Load the shader source from file
		std::string sSource = loadSourceFromFile(fsPath);

		LOG_INFO << "Loading shader from file: " << fsPath;
		return createShaderObject(sSource, eType);
	}

	boost::shared_ptr<ShaderObject> ShaderManager::createShaderObject(const std::string& sShaderSource, ShaderObject::ShaderType eType)
	{
		unsigned int uGLShaderType = ~0;
		std::string sShaderType;
		switch (eType)
		{
		case ShaderObject::VERTEX_SHADER: 
			uGLShaderType = GL_VERTEX_SHADER;
			sShaderType = "vertex";
			break;
		case ShaderObject::TESS_CONTROL_SHADER: 
			uGLShaderType = GL_TESS_CONTROL_SHADER;
			sShaderType = "tessellation control";
			break;
		case ShaderObject::TESS_EVALUATION_SHADER: 
			uGLShaderType = GL_TESS_EVALUATION_SHADER;
			sShaderType = "tessellation evaluation";
			break;
		case ShaderObject::GEOMETRY_SHADER: 
			uGLShaderType = GL_GEOMETRY_SHADER;
			sShaderType = "geometry";
			break;
		case ShaderObject::FRAGMENT_SHADER: 
			uGLShaderType = GL_FRAGMENT_SHADER;
			sShaderType = "fragment";
			break;
		case ShaderObject::COMPUTE_SHADER: 
			uGLShaderType = GL_COMPUTE_SHADER;
			sShaderType = "compute";
			break;
		default: assert(false); break; // This should never happen
		}

		// Create the shader
		LOG_INFO << "Creating " << sShaderType << " shader...";
		unsigned int uShaderObjectID = glCreateShader(uGLShaderType);

		// Commit the shader source to compiler
		const char* szShaderSource = sShaderSource.c_str();
		glShaderSource(uShaderObjectID, 1, (const char**)&szShaderSource, NULL);

		// Compile the shader
		LOG_INFO << "Compiling " << sShaderType << " shader...";
		glCompileShader(uShaderObjectID);

		// Get GLSL compiler status
		int iCompileStatus = 0;
		glGetShaderiv(uShaderObjectID, GL_COMPILE_STATUS, &iCompileStatus);
		if (iCompileStatus == GL_TRUE)
			LOG_INFO << "Successfully compiled " << sShaderType << " shader.";
		else
			LOG_ERROR << "Failed to compile " << sShaderType << " shader.";

		// Get GLSL compiler log
		int iLogLength = 0;
		glGetShaderiv(uShaderObjectID, GL_INFO_LOG_LENGTH, &iLogLength);
		char *szLog = new char[iLogLength + 1];
		glGetShaderInfoLog(uShaderObjectID, iLogLength, NULL, szLog);
		std::string sCompilerLog(szLog);
		delete[] szLog;
		LOG_INFO << sCompilerLog;

		assert(iCompileStatus == GL_TRUE);

		// Continue here
		// TODO: Create ShaderObject here
		auto spShaderObject = boost::shared_ptr<ShaderObject>();
		return spShaderObject;
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

	ShaderObject::ShaderType ShaderManager::getShaderObjectType(const std::string& sExtension)
	{
		if (sExtension == "vert")
			return ShaderObject::VERTEX_SHADER;
		else if (sExtension == "tesc")
			return ShaderObject::TESS_CONTROL_SHADER;
		else if (sExtension == "tese")
			return ShaderObject::TESS_EVALUATION_SHADER;
		else if (sExtension == "geom")
			return ShaderObject::GEOMETRY_SHADER;
		else if (sExtension == "frag")
			return ShaderObject::FRAGMENT_SHADER;
		else if (sExtension == "comp")
			return ShaderObject::COMPUTE_SHADER;
		else
			return ShaderObject::INVALID_SHADER;		
	}

} }