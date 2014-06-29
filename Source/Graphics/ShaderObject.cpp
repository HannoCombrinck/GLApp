#include "ShaderObject.h"

#include <GL/glew.h>
#include <Logging/Log.h>
#include <boost/unordered_map.hpp>
#include <boost/assign/list_of.hpp>

namespace baselib { namespace graphics {

	namespace
	{
		boost::unordered_map<ShaderObject::ShaderType, std::pair<std::string, unsigned int>> aShaderTypeMap = boost::assign::map_list_of
			(ShaderObject::VERTEX_SHADER,		   std::make_pair("vertex",					 GL_VERTEX_SHADER))
			(ShaderObject::TESS_CONTROL_SHADER,    std::make_pair("tessellation control",	 GL_TESS_CONTROL_SHADER))
			(ShaderObject::TESS_EVALUATION_SHADER, std::make_pair("tessellation evaluation", GL_TESS_EVALUATION_SHADER))
			(ShaderObject::GEOMETRY_SHADER,		   std::make_pair("geometry",				 GL_GEOMETRY_SHADER))
			(ShaderObject::FRAGMENT_SHADER,		   std::make_pair("fragment",				 GL_FRAGMENT_SHADER))
			(ShaderObject::COMPUTE_SHADER,		   std::make_pair("compute",				 GL_COMPUTE_SHADER))
			;

		unsigned int getGLShaderType(ShaderObject::ShaderType eType) { return aShaderTypeMap[eType].second;	}
		std::string getShaderTypeString(ShaderObject::ShaderType eType) { return aShaderTypeMap[eType].first; }
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