#pragma once

#include <assert.h>
#include <boost/shared_ptr.hpp>

#include <Math/Math.h>

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
				// Blend/Alpha states
				STATE_ALPHA_TEST,
				STATE_ALPHA_TEST_FUNC,
				STATE_ALPHA_TEST_REF,
				STATE_BLEND,
				STATE_BLEND_SRC,
				STATE_BLEND_DST,
				STATE_BLEND_OP,

				// Depth buffer states
				STATE_DEPTH_WRITE,
				STATE_DEPTH_TEST,
				STATE_DEPTH_FUNC,
				STATE_DEPTH_CLEAR_VALUE,
				
				// Rasterizer states
				STATE_CULL_MODE,
				STATE_DEPTH_BIAS,
				STATE_MULTISAMPLE,
				DEPTH_BIAS_NONE,
				DEPTH_BIAS_FILL,
				DEPTH_BIAS_LINE,
				DEPTH_BIAS_POINT,

				STATE_COUNT
			};

			enum RenderStateValues
			{
				UNINITIALIZED = 0,

				// Boolean values
				FALSE,
				TRUE,

				// Blend factor values
				ONE,
				SRC,
				SRC_ALPHA,
				DST,
				DST_ALPHA,
				ONE_MINUS_SRC,
				ONE_MINUS_SRC_ALPHA,
				ONE_MINUS_DST,
				ONE_MINUS_DST_ALPHA,

				// Blend operation values
				FUNC_ADD,
				FUNC_SUBTRACT,
				FUNC_REVERSE_SUBTRACT,
				FUNC_MIN,
				FUNC_MAX,

				// Cull mode values
				CULL_NONE,
				CULL_FRONT,
				CULL_BACK,
				CULL_FRONT_AND_BACK,

				STATE_VALUE_COUNT
			};

			enum ClearMasks
			{
				COLOUR_BUFFER = 1,
				DEPTH_BUFFER = 2,
				ACCUMULATION_BUFFER = 4,
				STENCIL_BUFFER = 8
			};

			//! Constructor.
			Renderer();
			//! Destructor.
			~Renderer();
		
			//! Create Geometry from a VertexList
			//boost::shared_ptr<Geometry> createGeometry(const boost::shared_ptr<VertexList>& spVertexList);

			//! Clear the current render target.
			void clear(unsigned int uMask);

			//! Set the clear colour.
			void setClearColour(const Vec4& v);
			//! Get the clear colour.
			Vec4 getClearColour() const { return m_vClearColour; }

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

			unsigned int m_auState[STATE_COUNT];  //!< Current render state values.
			Vec4 m_vClearColour;				  //!< Current clear colour. Current render target will be cleared to this colour when calling clear().

		};
	}
}