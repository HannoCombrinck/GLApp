#pragma once

#include <assert.h>
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

				STATE_COUNT
			};

			enum RenderStateValues
			{
				FALSE,
				TRUE,
				ONE,
				SRC,
				SRC_ALPHA,
				ONE_MINUS_SRC,
				ONE_MINUS_SRC_ALPHA,
				FRONT_FACE,
				BACK_FACE,

				STATE_VALUE_COUNT
			};

			//! Constructor.
			Renderer();
			//! Destructor.
			~Renderer();
		
			//! Create Geometry from a VertexList
			boost::shared_ptr<Geometry> createGeometry(const boost::shared_ptr<VertexList>& spVertexList);

			//! Set the current render state - ignores redundant changes.
			void setRenderState(unsigned int uState, unsigned int uValue);
			//! Get the current render state.
			unsigned int getRenderState(unsigned int uState) const { assert(uState < STATE_COUNT); return m_auState[uState]; }

		private:
			//! Initialize renderer.
			void init();
			//! Destroy renderer.
			void destroy();
			//! Apply a render state.
			void applyRenderState(unsigned int uState, unsigned int uValue);

			unsigned int m_auState[STATE_COUNT];

		};
	}
}