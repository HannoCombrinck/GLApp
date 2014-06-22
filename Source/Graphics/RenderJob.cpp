#include "RenderJob.h"

#include <Logging/Log.h>

namespace baselib { namespace graphics {

	RenderJob::RenderJob()
	{
		LOG_VERBOSE << "RenderJob constructor";
	}

	RenderJob::~RenderJob()
	{
		LOG_VERBOSE << "RenderJob destructor";
	}

} }