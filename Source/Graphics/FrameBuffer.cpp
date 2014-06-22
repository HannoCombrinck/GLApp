#include "FrameBuffer.h"

#include <Logging/Log.h>

namespace baselib { namespace graphics {

	FrameBuffer::FrameBuffer()
	{
		LOG_VERBOSE << "FrameBuffer constructor";
	}

	FrameBuffer::~FrameBuffer()
	{
		LOG_VERBOSE << "FrameBuffer destructor";
	}

} }