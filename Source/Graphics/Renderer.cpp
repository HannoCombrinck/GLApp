#include "Renderer.h"

#include <Logging/Log.h>

namespace baselib { namespace graphics {

	Renderer::Renderer()
	{
		LOG_VERBOSE << "Renderer constructor";
	}

	Renderer::~Renderer()
	{
		LOG_VERBOSE << "Renderer destructor";
	}

} }