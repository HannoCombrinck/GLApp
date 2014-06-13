#include "Shader.h"

#include <Logging/Log.h>
#include <GL/glew.h>

namespace baselib { namespace graphics {

	Shader::Shader(unsigned int uID)
		: m_uID(uID)
	{
		LOG_VERBOSE << "Shader constructor";
	}

	Shader::~Shader()
	{
		LOG_VERBOSE << "Shader destructor";
	}

	void Shader::bind()
	{
		glUseProgram(m_uID);
	}

	void Shader::unbind()
	{
		glUseProgram(0);
	}

	int Shader::getAttribute(const std::string& sName) const
	{
		assert(!sName.empty());
		int iAtrribute = glGetAttribLocation(m_uID, sName.c_str());
		assert(iAtrribute != -1);
		return iAtrribute;
	}

	int Shader::getUniform(const std::string& sName) const
	{
		assert(!sName.empty());
		int iUniform = glGetUniformLocation(m_uID, sName.c_str());
		assert(iUniform != -1);
		return iUniform;
	}

} }