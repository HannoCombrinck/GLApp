#pragma once

#include <boost/shared_ptr.hpp>

namespace baselib 
{
	namespace graphics
	{
		class Renderer;
		class Node;
		class VisualCollector;
		class FrameBuffer;
		class Camera;
	}
}

namespace baselib 
{
	namespace graphics
	{
		/*! @brief A RenderJob encapsulates the process of rendering a scene (Node hierarchy) from a given point of view (Camera) into a specified frame buffer (FrameBuffer).
		 *
		 *  A RenderJob renders the visuals contained in a Node hierarchy to the given frame buffer. 
		 *  A VisualCollector is used to cull visuals in this hierarchy and determine their rendering order.
		 *  A Camera is used to determine where the scene is rendered from (i.e. Camera provides view and projection matrices).
		 *  The scene is rendered into a FrameBuffer which can be the default back buffer or a set of textures setup as render targets.
		 */
		class RenderJob
		{
		public:
			//! Creates a RenderJob.
			static boost::shared_ptr<RenderJob> create(const boost::shared_ptr<Renderer>& spRenderer);

			//! Destructor.
			virtual ~RenderJob();

			//! Execute the job.
			void execute(const boost::shared_ptr<Node>& spNode,
						 const boost::shared_ptr<VisualCollector>& spVisualCollector,
						 const boost::shared_ptr<FrameBuffer>& spFrameBuffer,
						 const boost::shared_ptr<Camera>& spCamera);
		protected:
			//! Protected constructor - must be created by static create().
			RenderJob(const boost::shared_ptr<Renderer>& spRenderer);

		private:
			boost::shared_ptr<Renderer> m_spRenderer;

		};
	}
}