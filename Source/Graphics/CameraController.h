#pragma once

#include <Math/Math.h>
#include <boost/shared_ptr.hpp>

namespace baselib 
{
	namespace graphics
	{
		class Camera;
	}
}

namespace baselib 
{
	namespace graphics
	{
		/*! @brief CameraController calculates and sets camera state based on some control scheme e.g. free look cam
		 *
		 */
		class CameraController
		{
		public:
			//! Creates a CameraController.
			static boost::shared_ptr<CameraController> create(const boost::shared_ptr<Camera>& spCamera);

			//! Destructor.
			virtual ~CameraController();

			//! Update CameraController and set Camera state.
			void update(double dDeltaTime);

			//! Set the Camera to be controlled by this controller.
			void setCamera(const boost::shared_ptr<Camera>& spCamera) { m_spCamera = spCamera; }
			//! Getter for setCamera()
			boost::shared_ptr<Camera> getCamera() const { return m_spCamera; }

			//! Move the camera fDistance meters forward.
			void moveForward(float fDistance);
			//! Move the camera fDistance meters sideways.
			void moveSideways(float fDistance);
			//! Rotate fAngle degrees about the x-axis (pitch).
			void rotateX(float fAngle);
			//! Rotate fAngle degrees about the y-axis (yaw).
			void rotateY(float fAngle);
			//! Set camera position.
			void setPosition(const Vec3& v) { m_vPosition = v; m_bRecalcTransform = true; }
			//! Getter for setPosition().
			const Vec3& getPosition() const { return m_vPosition; }
			//! Set the camera pitch angle.
			void setPitch(float f) { m_fPitch = f; m_bRecalcTransform = true; }
			//! Getter for setPitch().
			float getPitch() const { return m_fPitch; }
			//! Set the camera yaw angle.
			void setYaw(float f) { m_fYaw = f; m_bRecalcTransform = true; }
			//! Getter for setYaw().
			float getYaw() const { return m_fYaw; }

		protected:
			//! Protected constructor - must be created by static create().
			CameraController(const boost::shared_ptr<Camera>& spCamera);

		private:
			boost::shared_ptr<Camera> m_spCamera; //!< The camera that is controlled by this controller.

			Vec3 m_vPosition;			//!< Camera position in world space.
			float m_fPitch;				//!< Camera pitch in degrees.
			float m_fYaw;				//!< Camera yaw in degrees.
			Mat4 m_mTransform;			//!< Camera transform calculated from position, yaw and pitch.
			bool m_bRecalcTransform;	//!< Set to true if the camera transform should be recalculated.
		};
	}
}