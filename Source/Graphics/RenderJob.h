#pragma once

#include <boost/shared_ptr.hpp>

namespace baselib 
{
	namespace graphics
	{
		/*! @brief A RenderJob encapsulates the process of rendering a scene (Node hierarchy) from a given point of view (Camera) into a specified render target.
		 *
		 *  A RenderJob renders the visuals contained a Node hierarchy to any given render target(s). 
		 *  A VisualCollector is used to cull visuals in this hierarchy and determine their rendering order.
		 *  A Camera is used to determine where the scene is rendered from (i.e. Camera provides view and projection matrices).
		 */
		class RenderJob
		{
		public:
			//! Constructor.
			RenderJob();
			//! Destructor.
			virtual ~RenderJob();

		private:

		};
	}
}