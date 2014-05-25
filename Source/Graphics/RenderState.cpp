#include "RenderState.h"

#include <Logging/Log.h>

namespace baselib { namespace graphics {

	RenderState::RenderState()
	{
		LOG_VERBOSE << "RenderState constructor";
	}

	RenderState::~RenderState()
	{
		LOG_VERBOSE << "RenderState destructor";
	}

} }