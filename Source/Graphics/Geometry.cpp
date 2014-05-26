#include "Geometry.h"

#include <Logging/Log.h>

namespace baselib { namespace graphics {

	Geometry::Geometry()
		: m_spVertexList(boost::shared_ptr<VertexList>())
		, m_uVAO(~0)
		, m_uVBO(~0)
		, m_uIB(~0)
	{
		LOG_VERBOSE << "Geometry constructor";
	}

	Geometry::Geometry(unsigned int uVAO, unsigned int uVBO, unsigned int uIB)
		: m_spVertexList(boost::shared_ptr<VertexList>())
		, m_uVAO(uVAO)
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