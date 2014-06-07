#pragma once

#include <boost/shared_ptr.hpp>

namespace baselib 
{
	namespace graphics
	{
		class Geometry;
		class VertexList;
	}
}

namespace baselib 
{
	namespace graphics
	{
		class Renderer
		{
		public:
			
			// Render states
			enum RenderStates
			{
				STATE_ALPHA_TEST,
				STATE_ALPHA_TEST_FUNC,
				STATE_ALPHA_TEST_REF,
				STATE_BLEND,
				STATE_BLEND_SRC,
				STATE_BLEND_DST,
				STATE_BLEND_FUNC,

				STATE_DEPTH_WRITE,
				STATE_DEPTH_TEST,
				STATE_DEPTH_FUNC,
				STATE_DEPTH_CLEAR_VALUE,
				
				STATE_CULL,
				STATE_CULL_MODE,
				STATE_DEPTH_BIAS,
				STATE_MULTISAMPLE,
			};

			//! Constructor.
			Renderer();
			//! Destructor.
			~Renderer();
		
			//! Create Geometry from a VertexList
			boost::shared_ptr<Geometry> createGeometry(const boost::shared_ptr<VertexList>& spVertexList);

		private:
			//! Initialize renderer.
			void init();
			//! Destroy renderer.
			void destroy();

		};
	}
}