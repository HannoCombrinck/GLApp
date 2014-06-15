#include "StaticGeometry.h"

#include <GL/glew.h>
#include <Logging/Log.h>

namespace baselib { namespace graphics {

	StaticGeometry::StaticGeometry(unsigned int uVAO, unsigned int uVBO, unsigned int uIB, PrimitiveType ePrimitiveType, const boost::shared_ptr<VertexListInterface>& spVertexList)
		: Geometry(uVAO, ePrimitiveType, spVertexList)
		, m_uVBO(uVBO)
		, m_uIB(uIB)
	{
		LOG_VERBOSE << "StaticGeometry constructor";
	}

	StaticGeometry::~StaticGeometry()
	{
		LOG_VERBOSE << "StaticGeometry destructor";
		glDeleteBuffers(1, &m_uVBO);
		glDeleteBuffers(1, &m_uIB);
	}

} }