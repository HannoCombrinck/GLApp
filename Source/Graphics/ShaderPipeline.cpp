#include "ShaderPipeline.h"

#include <GL/glew.h>
#include <Logging/Log.h>
#include <Graphics/Shader.h>
#include <Graphics/ShaderObject.h>
#include <boost/range/algorithm/for_each.hpp>

namespace baselib { namespace graphics {

	namespace
	{
		// Check for valid shader object combinations.
		bool isValidPipeline(const std::vector<boost::shared_ptr<ShaderObject>>& aspShaderObjects)
		{
			bool bValid = true;

			// Count number of shader objects per type.
			int iCount[ShaderObject::NUM_SHADER_TYPES];
			memset(iCount, 0, sizeof(int) * ShaderObject::NUM_SHADER_TYPES);

			boost::for_each(aspShaderObjects, [&iCount, &bValid](const boost::shared_ptr<ShaderObject>& spShaderObject) {
				ShaderObject::ShaderType eType = spShaderObject->getType();

				if (eType < 0 || eType >= ShaderObject::NUM_SHADER_TYPES)
				{
					LOG_ERROR << "Shader object has invalid type";
					assert(false);
				}

				iCount[eType] += 1;

				if (iCount[eType] > 1)
				{
					LOG_ERROR << "Only one shader object of each type is allowed per shader pipeline";
					bValid = false;
					return;
				}
			});

			// TODO: Check for valid shader object combinations

			//if (iCount[ShaderObject::VERTEX_SHADER] != 1)
			//	bValid = false;

			return bValid;
		}
	}

	boost::shared_ptr<ShaderPipeline> ShaderPipeline::create(const std::string& sName, const std::vector<boost::shared_ptr<ShaderObject>>& aspShaderObjects)
	{
		if (!isValidPipeline(aspShaderObjects))
		{
			LOG_ERROR << "Trying to create shader pipeline with invalid combination of shader objects";
			assert(false);
		}

		// Create shader program
		LOG_INFO << "Creating shader pipeline: " << sName;
		unsigned int uShaderProgramID = glCreateProgram();
		assert(uShaderProgramID);

		// Attach shader objects
		LOG_VERBOSE << "Attaching shader objects to pipeline";
		boost::for_each(aspShaderObjects, [&uShaderProgramID](const boost::shared_ptr<ShaderObject>& spShaderObject) {
			glAttachShader(uShaderProgramID, spShaderObject->getID());
		});

		// Link shader program
		LOG_VERBOSE << "Linking shader pipeline";
		glLinkProgram(uShaderProgramID);

		// Detach shader objects for release build only.
		// After linking a shader program the shader objects can be detached and are no longer needed.
		// Keeping them attached, and alive, is useful for debugging purposes though.
		// gDEBugger can, for example, rebuild and relink programs on the fly if they remain attached.
		#ifndef _DEBUG
		boost::for_each(aspShaderObjects, [&uShaderProgramID](const boost::shared_ptr<ShaderObject>& spShaderObject) {
			glDetachShader(uShaderProgramID, spShaderObject->getID());
		});
		#endif

		// Get linker status
		int iLinkStatus = 0;
		glGetProgramiv(uShaderProgramID, GL_LINK_STATUS, &iLinkStatus);

		// Get linker log
		int iLogLength = 0;
		glGetProgramiv(uShaderProgramID, GL_INFO_LOG_LENGTH, &iLogLength);
		char *szLog = new char[iLogLength + 1];
		glGetProgramInfoLog(uShaderProgramID, iLogLength, NULL, szLog);
		std::string sLinkerLog(szLog);
		delete[] szLog;

		if (!sLinkerLog.empty())
			LOG_INFO << sLinkerLog;

		// Check linker status
		if (iLinkStatus == GL_FALSE)
		{
			LOG_ERROR << "Failed to link shader pipeline";
			glDeleteProgram(uShaderProgramID);
			assert(false);
		}

		// Let the ShaderPipeline keep the shader objects alive for debug configurations. For release
		// configurations let them go out of scope and destroy the hardware buffers which are no longer required.
		#ifdef _DEBUG
		return boost::shared_ptr<ShaderPipeline>(new ShaderPipeline(sName, uShaderProgramID, aspShaderObjects));
		#else
		return boost::shared_ptr<ShaderPipeline>(new ShaderPipeline(sName, uShaderProgramID));
		#endif
	}

	ShaderPipeline::ShaderPipeline(const std::string& sName, unsigned int uID)
		: m_sName(sName)
		, m_uID(uID)
	{
		LOG_VERBOSE << "ShaderPipeline constructor";
	}

	ShaderPipeline::ShaderPipeline(const std::string& sName, unsigned int uID, const std::vector<boost::shared_ptr<ShaderObject>>& aspShaderObjects)
		: m_sName(sName)
		, m_uID(uID)
		, m_aspShaderObjects(aspShaderObjects)
	{
		LOG_VERBOSE << "ShaderPipeline debug constructor";
	}

	ShaderPipeline::~ShaderPipeline()
	{
		LOG_VERBOSE << "ShaderPipeline destructor";
		glDeleteProgram(m_uID);
	}

	boost::shared_ptr<Shader> ShaderPipeline::createInstance()
	{
		return boost::shared_ptr<Shader>(new Shader(m_uID));
	}

} }