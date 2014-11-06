#pragma once

#include <boost/shared_ptr.hpp>
#include <vector>

namespace baselib 
{
	namespace graphics
	{
		class Renderer;
		class Visual;
		class FrameBuffer;
		class Camera;
		class Shader;
	}
}

namespace baselib 
{
	namespace graphics
	{
		/*! @brief A RenderJob encapsulates the process of rendering a scene (list of Visuals) from a given point of view (Camera) into a specified frame buffer (FrameBuffer).
		 *
		 *  A RenderJob renders the list of visuals to the given frame buffer. A Camera is used to determine where the scene is rendered from.
		 *  The scene is rendered into the provided FrameBuffer which can be the default back buffer or a set of textures setup as render targets.
		 *  A shader can be passed in as well which then causes all visuals to be rendered with that shader as opposed to material define shaders.
		 */
		class RenderJob
		{
		public:
			//! Creates a RenderJob.
			static boost::shared_ptr<RenderJob> create(const boost::shared_ptr<Renderer>& spRenderer);

			//! Destructor.
			virtual ~RenderJob();

			//! Execute the job using shaders assigned to visual materials.
			void execute(const std::vector<Visual*>& apVisuals,
						 const boost::shared_ptr<FrameBuffer>& spFrameBuffer,
						 const boost::shared_ptr<Camera>& spCamera,
						 bool bClear = true);

			//! Execute the job using the provided shader.
			void execute(const std::vector<Visual*>& apVisuals,
						 const boost::shared_ptr<FrameBuffer>& spFrameBuffer,
						 const boost::shared_ptr<Camera>& spCamera,
						 const boost::shared_ptr<Shader>& spShader,
						 bool bClear = true);
		protected:
			//! Protected constructor - must be created by static create().
			RenderJob(const boost::shared_ptr<Renderer>& spRenderer);

		private:
			boost::shared_ptr<Renderer> m_spRenderer;

		};
	}
}