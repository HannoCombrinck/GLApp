#pragma once

#include <Math/Math.h>
#include <memory>

namespace baselib 
{
	namespace graphics
	{
		/*! @brief Camera 
		 *
		 */
		class Camera
		{
		public:
			//! Camera projection mode.
			enum ProjectionMode
			{
				ORTHOGRAPHIC,
				PERSPECTIVE
			};

			//! Creates a Camera.
			static std::shared_ptr<Camera> create();

			//! Destructor.
			virtual ~Camera();

			//! Get the view matrix.
			const Mat4& getViewMatrix() const;
			//! Get the projection matrix.
			const Mat4& getProjectionMatrix() const;

			//! Set the transform matrix.
			void setTransform(const Mat4& m) { m_mTransform = m; m_bRecalcViewMatrix = true; }
			//! Getter for setTransform().
			const Mat4& getTransform() const { return m_mTransform; }
			//! Set the projection mode.
			void setProjectionMode(ProjectionMode eMode) { m_eProjectionMode = eMode; m_bRecalcProjectionMatrix = true; }
			//! Getter for setProjectionMode().
			ProjectionMode getProjectionMode() const { return m_eProjectionMode; }
			//! Set the camera field of view.
			void setFOV(float f) { m_fFOV = f; m_bRecalcProjectionMatrix = true; }
			//! Getter for setFOV().
			float getFOV() const { return m_fFOV; }
			//! Set the camera aspect ratio to use for perspective projection.
			void setAspectRatio(float f) { m_fAspectRatio = f; m_bRecalcProjectionMatrix = true; }
			//! Getter for setAspectRatio().
			float getAspectRatio() const { return m_fAspectRatio; }
			//! Set the camera width to use for orthographic projection.
			void setOrthoWidth(float f) { m_fOrthoWidth = f; m_bRecalcProjectionMatrix = true; }
			//! Getter for setOrthoWidth().
			float getOrthoWidth() const { return m_fOrthoWidth; }
			//! Set the camera height to use for orthographic projection.
			void setOrthoHeight(float f) { m_fOrthoHeight = f; m_bRecalcProjectionMatrix = true;}
			//! Getter for setOrthoHeight().
			float getOrthoHeight() const { return m_fOrthoHeight; }
			//! Set the camera near clipping distance.
			void setNearClipDistance(float f) { m_fNearClipDistance = f; m_bRecalcProjectionMatrix = true; }
			//! Getter for setNearClipDistance().
			float getNearClipDistance() const { return m_fNearClipDistance; }
			//! Set the camera far clipping distance.
			void setFarClipDistance(float f) { m_fFarClipDistance = f; m_bRecalcProjectionMatrix = true; }
			//! Getter for setFarClipDistance().
			float getFarClipDistance() const { return m_fFarClipDistance; }

		protected:
			//! Protected constructor - must be created by static create().
			Camera();

		private:
			mutable Mat4 m_mView;					//!< Cached view matrix.
			mutable Mat4 m_mProjection;				//!< Cached projection matrix.
			mutable bool m_bRecalcViewMatrix;		//!< Set to true if the view matrix parameters have changed and should be recalculated.
			mutable bool m_bRecalcProjectionMatrix;	//!< Set to ture if the projection matrix parameters have changed and should be recalculated.

			Mat4 m_mTransform;				  //!< Transform matrix from which defines the camera's position and orientation.
			ProjectionMode m_eProjectionMode; //!< The camera's projection mode i.e orthographic or perspective
			float m_fFOV;					  //!< Camera field of view in degrees.
			float m_fAspectRatio;			  //!< Frustum aspect ratio to use for perspective projection.
			float m_fOrthoWidth;			  //!< Frustum width to use for orthographic projection.
			float m_fOrthoHeight;			  //!< Frustum height to use for orthographic projection.
			float m_fNearClipDistance;		  //!< Distance in meters to camera's near clipping plane.
			float m_fFarClipDistance;		  //!< Distance in meters to camera's far clipping plane.
		};
	}
}