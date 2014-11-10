#include "Shader.h"

#include <Logging/Log.h>
#include <Graphics/ShaderPipeline.h>
#include <GL/glew.h>

namespace baselib { namespace graphics {

	unsigned int Shader::m_uCurrentlyBound = ~0;

	Shader::Shader(const boost::shared_ptr<ShaderPipeline>& spShaderPipeline)
		: m_spShaderPipeline(spShaderPipeline)
		, m_uID(spShaderPipeline->getID())
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

	bool Shader::getUniform(int& iIndex, const std::string& sName) const
	{
		const GLchar* szName = sName.c_str();
		iIndex = glGetUniformLocation(m_uID, szName);
		if (iIndex != -1)
			return true;
		return false;
	}

	void Shader::setUniform(int iIndex, float f)
	{
		glUniform1f(iIndex, f);
	}

	void Shader::setUniform(const std::string& sName, float f)
	{
		int iIndex = -1;
		if (getUniform(iIndex, sName))
			setUniform(iIndex, f);
	}

	void Shader::setUniform(int iIndex, const Vec2& v)
	{
		glUniform2f(iIndex, v.x, v.y);
	}

	void Shader::setUniform(int iIndex, const Vec3& v)
	{
		glUniform3f(iIndex, v.x, v.y, v.z);
	}

	void Shader::setUniform(int iIndex, const Vec4& v)
	{
		glUniform4f(iIndex, v.x, v.y, v.z, v.w);
	}

	void Shader::setUniform(const std::string& sName, const Vec3& v)
	{
		int iIndex = -1;
		if (getUniform(iIndex, sName))
			setUniform(iIndex, v);
	}

	void Shader::setUniform(int iIndex, const Mat4& m)	
	{
		glUniformMatrix4fv(iIndex, 1, GL_FALSE, glm::value_ptr(m));
	}

	void Shader::setUniform(const std::string& sName, const Mat4& m)
	{
		int iIndex = -1;
		if (getUniform(iIndex, sName))
			setUniform(iIndex, m);
	}

	void Shader::setUniform(int iIndex, int i)
	{
		glUniform1i(iIndex, i);
	}

	void Shader::setUniform(const std::string& sName, int i)
	{
		int iIndex = -1;
		if (getUniform(iIndex, sName))
			setUniform(iIndex, i);
	}

} }