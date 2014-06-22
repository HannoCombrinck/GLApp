#include "VisualCollector.h"

#include <Logging/Log.h>

namespace baselib { namespace graphics {

	VisualCollector::VisualCollector()
	{
		LOG_VERBOSE << "VisualCollector constructor";
	}

	VisualCollector::~VisualCollector()
	{
		LOG_VERBOSE << "VisualCollector destructor";
	}

} }