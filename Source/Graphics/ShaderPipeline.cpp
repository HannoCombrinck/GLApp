#include "ShaderPipeline.h"

#include <GL/glew.h>
#include <Logging/Log.h>
#include <Graphics/Shader.h>

namespace baselib { namespace graphics {

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