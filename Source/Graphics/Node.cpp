#include "Node.h"

#include <Logging/Log.h>

namespace baselib { namespace graphics {

	Node::Node()
	{
		LOG_VERBOSE << "Node constructor";
	}

	Node::~Node()
	{
		LOG_VERBOSE << "Node destructor";
	}

} }