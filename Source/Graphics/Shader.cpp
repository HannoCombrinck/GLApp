#include "Shader.h"

#include <Logging/Log.h>
#include <GL/glew.h>

namespace baselib { namespace graphics {

	unsigned int Shader::m_uCurrentlyBound = ~0;

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
		if (m_uID == m_uCurrentlyBound)
			return;

		glUseProgram(m_uID);
		m_uCurrentlyBound = m_uID;
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
		const GLchar* szName = sName.c_str();
		int iUniform = glGetUniformLocation(m_uID, szName);
		assert(iUniform != -1);
		return iUniform;
	}

	void Shader::setUniform(int iIndex, float f)
	{
		glUniform1f(iIndex, f);
	}

	void Shader::setUniform(int iIndex, Vec2 v)
	{
		glUniform2f(iIndex, v.x, v.y);
	}

	void Shader::setUniform(int iIndex, Vec3 v)
	{
		glUniform3f(iIndex, v.x, v.y, v.z);
	}

	void Shader::setUniform(int iIndex, Vec4 v)
	{
		glUniform4f(iIndex, v.x, v.y, v.z, v.w);
	}

	void Shader::setUniform( int iIndex, int i )
	{
		glUniform1i(iIndex, i);
	}

} }