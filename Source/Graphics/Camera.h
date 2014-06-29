#pragma once

#include <Math/Math.h>
#include <Graphics/Spatial.h>

namespace baselib 
{
	namespace graphics
	{
		/*! @brief Frustum  
		 *
		 */
		class Frustum
		{
		public:
			Frustum() {}
			~Frustum() {}
		};

		/*! @brief Camera 
		 *
		 */
		class Camera : public Spatial
		{
		public:
			//! Creates a Camera.
			static boost::shared_ptr<Camera> create();

			//! Destructor.
			virtual ~Camera();

			//! Get the view matrix.
			const Mat4& getViewMatrix() const { return m_mView; }
			//! Get the projection matrix.
			const Mat4& getProjectionMatrix() const { return m_mProjection; }
			//! Get the camera frustum.
			const Frustum& getFrustum() const { return m_Frustum; }

		protected:
			//! Protected constructor - must be created by static create().
			Camera();

		private:
			Mat4 m_mView;
			Mat4 m_mProjection;
			Frustum m_Frustum;

		};
	}
}