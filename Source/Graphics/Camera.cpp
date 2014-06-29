#include "Camera.h"

#include <Logging/Log.h>

namespace baselib { namespace graphics {

	boost::shared_ptr<Camera> Camera::create()
	{
		return boost::shared_ptr<Camera>(new Camera());
	}

	Camera::Camera()
		: m_mView(Mat4())
		, m_mProjection(Mat4())
	{
		LOG_VERBOSE << "Camera constructor";
	}

	Camera::~Camera()
	{
		LOG_VERBOSE << "Camera destructor";
	}

} }