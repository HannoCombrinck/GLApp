#include "Geometry.h"

#include <GL/glew.h>
#include <Logging/Log.h>

namespace baselib { namespace graphics {

	Geometry::Geometry(unsigned int uVAO, PrimitiveType ePrimitiveType, const boost::shared_ptr<VertexListInterface>& spVertexList)
		: m_uVAO(uVAO)
		, m_ePrimitiveType(ePrimitiveType)
		, m_spVertexList(spVertexList)
	{
		LOG_VERBOSE << "Geometry constructor";
	}

	Geometry::~Geometry()
	{
		LOG_VERBOSE << "Geometry destructor";
		glDeleteBuffers(1, &m_uVAO);
	}

	void Geometry::bind()
	{
		glBindVertexArray(m_uVAO);
	}

	void Geometry::unbind()
	{
		glBindVertexArray(0);
	}

} }