#include "ShaderObject.h"

#include <GL/glew.h>

#include <Logging/Log.h>

namespace baselib { namespace graphics {

	ShaderObject::ShaderObject(const std::string& sName, ShaderType eType, unsigned int iID, const std::string& sSource)
		: m_sName(sName)
		, m_eType(eType)
		, m_uID(iID)
		, m_sSource(sSource)
	{
		LOG_VERBOSE << "ShaderObject constructor";
	}

	ShaderObject::~ShaderObject()
	{
		LOG_VERBOSE << "ShaderObject destructor";
		glDeleteShader(getID());
	}

} }