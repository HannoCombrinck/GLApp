#include "ShaderObject.h"

#include <Logging/Log.h>
#include <Graphics/ShaderManager.h>

namespace baselib { namespace graphics {

	ShaderObject::ShaderObject(const std::string& sName, ShaderType eType, unsigned int iID, const std::string& sSource, const boost::shared_ptr<ShaderManager>& spShaderManager)
		: m_sName(sName)
		, m_eType(eType)
		, m_uID(iID)
		, m_sSource(sSource)
		, m_wpShaderManager(spShaderManager)
	{
		LOG_VERBOSE << "ShaderObject constructor";
	}

	ShaderObject::~ShaderObject()
	{
		LOG_VERBOSE << "ShaderObject destructor";
		if (auto spShaderManager = m_wpShaderManager.lock())
		{
			spShaderManager->destroyShaderObject(getID());
			setID(~0);
		}
		else
		{
			LOG_ERROR << "ShaderManager destroyed before all shader objects destroyed";
			assert(false);
		}
	}

} }