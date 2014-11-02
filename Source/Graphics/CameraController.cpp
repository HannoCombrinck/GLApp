#include "CameraController.h"

#include <Logging/Log.h>
#include <Math/MathHelpers.h>
#include <Graphics/Camera.h>

namespace baselib { namespace graphics {

	boost::shared_ptr<CameraController> CameraController::create(const boost::shared_ptr<Camera>& spCamera)
	{
		return boost::shared_ptr<CameraController>(new CameraController(spCamera));
	}

	CameraController::CameraController(const boost::shared_ptr<Camera>& spCamera)
		: m_spCamera(spCamera)
		, m_vPosition(Vec3(0.0f))
		, m_fPitch(0.0f)
		, m_fYaw(0.0f)
		, m_mTransform(Mat4())
		, m_bRecalcTransform(true)
		, m_bMovingForward(false)
		, m_bMovingBack(false)
		, m_bMovingLeft(false)
		, m_bMovingRight(false)
	{
		LOG_VERBOSE << "CameraController constructor";
	}

	CameraController::~CameraController()
	{
		LOG_VERBOSE << "CameraController destructor";
	}

	void CameraController::update( double dDeltaTime )
	{
		if (!m_spCamera)
			return;

		if (m_bMovingForward)
			moveForward(0.3f);
		if (m_bMovingBack)
			moveForward(-0.3f);
		if (m_bMovingLeft)
			moveSideways(-0.3f);
		if (m_bMovingRight)
			moveSideways(0.3f);

		if (m_bRecalcTransform)
		{
			m_mTransform = Mat4(1.0);
			m_mTransform = glm::translate(m_mTransform, m_vPosition);
			m_mTransform = glm::rotate(m_mTransform, toRadians(m_fYaw), Vec3(0.0, 1.0, 0.0));
			m_mTransform = glm::rotate(m_mTransform, toRadians(m_fPitch), Vec3(1.0, 0.0, 0.0));

			m_spCamera->setTransform(m_mTransform);

			m_bRecalcTransform = false;
		}
	}

	void CameraController::moveForward(float fDistance)
	{
		m_vPosition.x += fDistance * sin(toRadians(m_fYaw)) * cos(toRadians(m_fPitch));
		m_vPosition.y -= fDistance * sin(toRadians(m_fPitch));
		m_vPosition.z -= fDistance * cos(toRadians(m_fYaw)) * cos(toRadians(m_fPitch));

		m_bRecalcTransform = true;
	}

	void CameraController::moveSideways(float fDistance)
	{
		m_vPosition.x += fDistance * cos(toRadians(m_fYaw));
		m_vPosition.z += fDistance * sin(toRadians(m_fYaw));

		m_bRecalcTransform = true;
	}

	void CameraController::rotateX(float fAngle)
	{
		m_fPitch += fAngle;

		if (m_fPitch <= -90.0f)
			m_fPitch = -90.0f;
		else if (m_fPitch >= 90.0f)
			m_fPitch = 90.0f;

		m_bRecalcTransform = true;
	}

	void CameraController::rotateY(float fAngle)
	{
		m_fYaw += fAngle;

		if (m_fYaw <= 0)
			m_fYaw = 360.0f + m_fYaw;
		else if (m_fYaw >= 360.0f)
			m_fYaw = m_fYaw - 360.0f;

		m_bRecalcTransform = true;
	}

} }