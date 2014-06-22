#include "Camera.h"

#include <Logging/Log.h>

namespace baselib { namespace graphics {

	Camera::Camera()
	{
		LOG_VERBOSE << "Camera constructor";
	}

	Camera::~Camera()
	{
		LOG_VERBOSE << "Camera destructor";
	}

} }