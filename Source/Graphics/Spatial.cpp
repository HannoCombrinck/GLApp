#include "Spatial.h"

#include <Logging/Log.h>

namespace baselib { namespace graphics {

	Spatial::Spatial()
		: m_sName("Spatial")
		, m_mLocal(Mat4())
		, m_mWorld(Mat4())
		, m_bUseLocalAsWorld(false)
	{
		LOG_VERBOSE << "Spatial constructor";
	}

	Spatial::~Spatial()
	{
		LOG_VERBOSE << "Spatial destructor";
	}

	void Spatial::update(const Mat4& mParent)
	{
		if (m_bUseLocalAsWorld)
			m_mWorld = m_mLocal;
		else
			m_mWorld = mParent * m_mLocal;
	}

} }