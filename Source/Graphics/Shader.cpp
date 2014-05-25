#include "Shader.h"

#include <Logging/Log.h>

namespace baselib { namespace graphics {

	Shader::Shader()
	{
		LOG_VERBOSE << "Shader constructor";
	}

	Shader::~Shader()
	{
		LOG_VERBOSE << "Shader destructor";
	}

} }