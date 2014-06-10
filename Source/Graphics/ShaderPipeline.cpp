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

	ShaderPipeline::~ShaderPipeline()
	{
		LOG_VERBOSE << "ShaderPipeline destructor";
		glDeleteProgram(getID());
	}

	boost::shared_ptr<Shader> ShaderPipeline::createShader()
	{
		return boost::shared_ptr<Shader>();
	}

} }