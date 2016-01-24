#include "Camera.h"

#include <Logging/Log.h>
#include <Math/MathHelpers.h>

namespace baselib { namespace graphics {

	std::shared_ptr<Camera> Camera::create()
	{
		return std::shared_ptr<Camera>(new Camera());
	}

	Camera::Camera()
		: m_mView(Mat4())
		, m_mProjection(Mat4())
		, m_bRecalcViewMatrix(true)
		, m_bRecalcProjectionMatrix(true)
		, m_mTransform(Mat4())
		, m_eProjectionMode(PERSPECTIVE)
		, m_fFOV(70.0f)
		, m_fAspectRatio(4.0f/3.0f)
		, m_fOrthoWidth(1.0f)
		, m_fOrthoHeight(1.0f)
		, m_fNearClipDistance(0.1f)
		, m_fFarClipDistance(10000.0f)
	{
		LOG_VERBOSE << "Camera constructor";
	}

	Camera::~Camera()
	{
		LOG_VERBOSE << "Camera destructor";
	}

	const Mat4& Camera::getViewMatrix() const
	{
		if (m_bRecalcViewMatrix)
		{
			m_mView = glm::inverse(m_mTransform);
			m_bRecalcViewMatrix = false;
		}

		return m_mView;
	}

	const Mat4& Camera::getProjectionMatrix() const
	{
		if (m_bRecalcProjectionMatrix)
		{
			if (m_eProjectionMode == PERSPECTIVE)
				m_mProjection = glm::perspective(toRadians(m_fFOV), m_fAspectRatio, m_fNearClipDistance, m_fFarClipDistance);
			else if (m_eProjectionMode == ORTHOGRAPHIC)
				m_mProjection = glm::ortho(0.0f, m_fOrthoWidth, 0.0f, m_fOrthoHeight);

			m_bRecalcProjectionMatrix = false;
		}

		return m_mProjection;
	}

} }