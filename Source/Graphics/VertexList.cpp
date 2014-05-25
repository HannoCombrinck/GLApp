#include "VertexList.h"

#include <Logging/Log.h>

namespace baselib { namespace graphics {

	VertexList::VertexList()
	{
		LOG_VERBOSE << "VertexList constructor";
	}

	VertexList::~VertexList()
	{
		LOG_VERBOSE << "VertexList destructor";
	}

	void VertexList::clear()
	{
		m_aVertices.clear();
		m_aIndices.clear();
	}

} }