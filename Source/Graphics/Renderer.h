#pragma once

#include <assert.h>
#include <Math/Math.h>

#include <Graphics/Geometry.h>

namespace baselib 
{
	namespace graphics
	{
		class StaticGeometry;
		class VertexListInterface;
		class Material;
		class FrameBuffer;
	}
}

namespace baselib 
{
	namespace graphics
	{
		/*! @brief Renderer interface. Wrapper for OpenGL API.
		 *
		 */
		class Renderer
		{
		public:
			
			// Render states
			enum RenderState
			{
				INVALID_RENDER_STATE,

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
				STATE_FILL_MODE,
				STATE_CULL_MODE,
				STATE_DEPTH_BIAS,
				STATE_MULTISAMPLE,
				DEPTH_BIAS_NONE,
				DEPTH_BIAS_FILL,
				DEPTH_BIAS_LINE,
				DEPTH_BIAS_POINT,

				STATE_COUNT
			};

			enum RenderStateValue
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

				// Polygon fill mode values
				FILL,
				LINE,
				POINT,

				STATE_VALUE_COUNT
			};

			enum ClearMask
			{
				COLOUR_BUFFER = 1,
				DEPTH_BUFFER = 2,
				STENCIL_BUFFER = 4
			};

			//! Constructor.
			Renderer();
			//! Destructor.
			virtual ~Renderer();
		
			//! Draw indexed geometry defined by the buffers in the currently bound VAO.
			void drawIndexed(Geometry::PrimitiveType ePrimitiveType, unsigned int uIndexCount, unsigned int uIndexOffset);

			//! Bind material - ignores redundant changes.
			void bindMaterial(const boost::shared_ptr<Material>& spMaterial);

			//! Bind frame buffer - ignores redundant changes.
			void bindFrameBuffer(const boost::shared_ptr<FrameBuffer>& spFrameBuffer);

			//! Flush the pipeline.
			void flush();

			//! Clear all buffers for current render target.
			void clear();
			//! Clear buffers specified by mask for current render target.
			void clear(ClearMask eMask);

			//! Set the active view port size.
			void setViewportSize(const Vec4& vViewport);
			//! Get the active view port size.
			Vec4 getViewportSize() const { return m_vViewportSize; }

			//! Set the clear colour.
			void setClearColour(const Vec4& v);
			//! Get the clear colour.
			Vec4 getClearColour() const { return m_vClearColour; }

			//! Set the current render state - ignores redundant changes.
			void setRenderState(RenderState eState, RenderStateValue eValue);
			//! Get the current value of a render state.
			RenderStateValue getRenderState(RenderState eState) const { assert(eState < STATE_COUNT); return m_aeState[eState]; }

			//! Create a static geometry.
			boost::shared_ptr<StaticGeometry> createStaticGeometry(const boost::shared_ptr<VertexListInterface>& spVertexList, Geometry::PrimitiveType ePrimitiveType);

		private:
			//! Initialize renderer.
			void init();
			//! Destroy renderer.
			void destroy();
			//! Apply a render state.
			void applyRenderState(RenderState eState, RenderStateValue eValue);
			
			Vec4 m_vClearColour;					  //!< Current clear colour. Current render target will be cleared to this colour when calling clear().
			Vec4 m_vViewportSize;					  //!< Current viewport size.
			RenderStateValue m_aeState[STATE_COUNT];  //!< Current render state values.
			unsigned int m_uBoundShader;			  //!< Currently bound shader program.
			unsigned int m_uBoundTexture;			  //!< Currently bound texture.
			unsigned int m_uActiveTextureUnit;		  //!< The active texture unit.
			unsigned int m_uBoundFramebuffer;		  //!< Currently bound frame buffer object.

		};
	}
}