#include "ShaderObject.h"

#include <Logging/Log.h>

namespace baselib { namespace graphics {

	ShaderObject::ShaderObject(const std::string& sSource, ShaderType eType)
		: m_sSource(sSource)
		, m_eType(eType)
		, m_uID(~0)
	{
		LOG_VERBOSE << "ShaderObject constructor";
	}

	ShaderObject::~ShaderObject()
	{
		LOG_VERBOSE << "ShaderObject destructor";
	}

	void ShaderObject::init()
	{

	}

} }