#include "Geometry.h"

#include <Logging/Log.h>

namespace baselib { namespace graphics {

	Geometry::Geometry(unsigned int uVAO)
		: m_uVAO(uVAO)
	{
		LOG_VERBOSE << "Geometry constructor";
	}

	Geometry::~Geometry()
	{
		LOG_VERBOSE << "Geometry destructor";
	}

} }