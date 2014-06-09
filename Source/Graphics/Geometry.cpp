#include "Geometry.h"

#include <Logging/Log.h>

namespace baselib { namespace graphics {

	Geometry::Geometry(unsigned int uVAO, unsigned int uVBO, unsigned int uIB)
		: m_uVAO(uVAO)
		, m_uVBO(uVBO)
		, m_uIB(uIB)
	{
		LOG_VERBOSE << "Geometry constructor";
	}

	Geometry::~Geometry()
	{
		LOG_VERBOSE << "Geometry destructor";
	}

} }