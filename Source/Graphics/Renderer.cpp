#include "Renderer.h"

#include <GL/glew.h>
#include <Logging/Log.h>
#include <Graphics/VertexList.h>
#include <Graphics/StaticGeometry.h>

#include <boost/range/algorithm/for_each.hpp>

namespace baselib { namespace graphics {

	Renderer::Renderer()
	{
		LOG_VERBOSE << "Renderer constructor";
		init();
	}

	Renderer::~Renderer()
	{
		LOG_VERBOSE << "Renderer destructor";
		destroy();
	}

	void Renderer::init()
	{
		// Temp Should set to default OpenGL states.
		memset(m_aeState, 0, sizeof(unsigned int)*STATE_COUNT);
		m_aeState[STATE_BLEND_DST] = ONE;
		m_aeState[STATE_BLEND_SRC] = ONE;

		//////////////////////////////////////////////////////////////////////////
		// Temp settings for testing - these will be encapsulated elsewhere
		setClearColour(Vec4(0.0f, 0.0f, 0.0f, 0.0f));
		setRenderState(STATE_DEPTH_TEST, TRUE);
		setRenderState(STATE_CULL_MODE, CULL_NONE);
		setRenderState(STATE_BLEND, FALSE);
		setRenderState(STATE_BLEND_SRC, SRC_ALPHA);
		setRenderState(STATE_BLEND_DST, ONE_MINUS_SRC_ALPHA);

		glViewport(0, 0, 640, 480);
		//////////////////////////////////////////////////////////////////////////
	}

	void Renderer::destroy()
	{

	}


	void Renderer::drawIndexed(PrimitiveType ePrimitiveType, unsigned int uIndexCount, unsigned int uIndexType, unsigned int uIndexOffset)
	{
		glDrawElements(GL_TRIANGLES, uIndexCount, uIndexType, (const GLvoid*) uIndexOffset);
	}

	//void Renderer::draw(const boost::shared_ptr<Geometry>& spGeometry)
	//{
	//	// For now assume all geometries have index buffers.
	//	glBindVertexArray(spGeometry->getVAO());
	//	//glDrawElements(GL_TRIANGLES, /*num indices*/, /*index type i.e. unsigned int*/, /*offset into index buffer*/)
	//	glBindVertexArray(0);
	//	assert(false);
	//}

	void Renderer::clear()
	{
		clear(ClearMask(COLOUR_BUFFER | DEPTH_BUFFER | STENCIL_BUFFER));
	}

	void Renderer::clear(ClearMask eMask)
	{
		unsigned int uGLMask = 0;
		uGLMask |= (eMask & COLOUR_BUFFER) ? GL_COLOR_BUFFER_BIT : 0;
		uGLMask |= (eMask & DEPTH_BUFFER) ? GL_DEPTH_BUFFER_BIT : 0;
		uGLMask |= (eMask & STENCIL_BUFFER) ? GL_STENCIL_BUFFER_BIT : 0;

		glClear(uGLMask);
	}

	void Renderer::setViewport(const Vec4& vViewport)
	{
		glViewport(int(vViewport.x), int(vViewport.y), int(vViewport.z), int(vViewport.w));
	}

	void Renderer::setClearColour(const Vec4& v)
	{
		glClearColor(v.r, v.g, v.b, v.a);
		m_vClearColour = v;
	}

	void Renderer::setRenderState(RenderState eState, RenderStateValue eValue)
	{
		assert(eState < STATE_COUNT);

		if (m_aeState[eState] == eValue)
		{
			LOG_VERBOSE << "Ignoring redundant state change";
			return;
		}

		m_aeState[eState] = eValue;
		applyRenderState(eState, eValue);
	}

	namespace
	{
		GLenum getGLType(unsigned int uType)
		{
			switch (uType)
			{
			case TYPE_FLOAT: return GL_FLOAT; break;
			case TYPE_INT: return GL_INT; break;
			case TYPE_BOOL: return GL_BOOL; break;
			default: assert(false); return 0; break;
			}
		}

		GLboolean getGLBool(bool bValue)
		{
			if (bValue) 
				return GL_TRUE;
			return GL_FALSE;
		}
	}

	boost::shared_ptr<StaticGeometry> Renderer::createStaticGeometry(const boost::shared_ptr<VertexListInterface>& spVertexList)
	{
		LOG_DEBUG << "Creating static geometry hardware buffers";
		
		// Create VAO
		unsigned int uVAO = ~0;
		glGenVertexArrays(1, &uVAO);
		glBindVertexArray(uVAO);

		// Create vertex buffer (VBO)
		unsigned int uVBO = ~0;
		glGenBuffers(1, &uVBO);
		glBindBuffer(GL_ARRAY_BUFFER, uVBO);
		glBufferData(GL_ARRAY_BUFFER, spVertexList->getVertexBufferSize(), spVertexList->getVertexBufferData(), GL_STATIC_DRAW);

		// Set vertex attribute layouts
		auto spVertexLayout = spVertexList->getVertexLayout();
		int iVertexSize = spVertexList->getVertexSize();
		auto aAttributes = spVertexLayout->getAttributes();
		boost::for_each(aAttributes, [iVertexSize](const VertexAttribute& va) {
			glVertexAttribPointer(va.iIndex, va.iNumElements, getGLType(va.uType), getGLBool(va.bNormalized), iVertexSize, (const GLvoid*)va.iOffset); // Cast offset parameter to (const GLVoid*) because of legacy glVertexAttribPointer() function prototype. It should just be an int.
			glEnableVertexAttribArray(va.iIndex);
		});

		// Create index buffer
		unsigned int uIB = ~0;
		glGenBuffers(1, &uIB);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uIB);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, spVertexList->getIndexBufferSize(), spVertexList->getIndexBufferData(), GL_STATIC_DRAW);

		// Unbind VAO - the VBO state is contained in VAO so unbinding VAO also unbinds VBO.
		// If VBO's are unbinded here they are removed from VAO state and isn't valid anymore.
		//glBindBuffer(GL_ARRAY_BUFFER, 0);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		LOG_DEBUG << "Successfully created static geometry hardware buffers";
		return boost::shared_ptr<StaticGeometry>(new StaticGeometry(uVAO, uVBO, uIB));
	}

	namespace
	{
		void enableGLState(unsigned int uGLState, Renderer::RenderStateValue eValue)
		{
			switch (eValue)
			{
			case Renderer::TRUE: glEnable(uGLState); break;
			case Renderer::FALSE: glDisable(uGLState); break;
			default: LOG_ERROR << "Invalid render state value - expected TRUE or FALSE"; assert(false); break;
			}
		}

		unsigned int getGLBlendFactor(Renderer::RenderStateValue eBlendFactor)
		{
			switch (eBlendFactor)
			{
			case Renderer::ONE: return GL_ONE; break;
			case Renderer::SRC: return GL_SRC_COLOR; break;
			case Renderer::SRC_ALPHA: return GL_SRC_ALPHA; break;
			case Renderer::DST: return GL_DST_COLOR; break;
			case Renderer::DST_ALPHA: return GL_DST_ALPHA; break;
			case Renderer::ONE_MINUS_SRC: return GL_ONE_MINUS_SRC_COLOR; break;
			case Renderer::ONE_MINUS_SRC_ALPHA: return GL_ONE_MINUS_SRC_ALPHA; break;
			case Renderer::ONE_MINUS_DST: return GL_ONE_MINUS_DST_COLOR; break;
			case Renderer::ONE_MINUS_DST_ALPHA: return GL_ONE_MINUS_DST_ALPHA; break;
			default: LOG_ERROR << "Invalid render state value - expected blend factor value"; assert(false); return 0; break;
			}
		}

		unsigned int getGLBlendOp(Renderer::RenderStateValue eBlendOp)
		{
			switch (eBlendOp)
			{
			case Renderer::FUNC_ADD: return GL_FUNC_ADD; break;
			case Renderer::FUNC_SUBTRACT: return GL_FUNC_SUBTRACT; break;
			case Renderer::FUNC_REVERSE_SUBTRACT: return GL_FUNC_REVERSE_SUBTRACT; break;
			case Renderer::FUNC_MIN: return GL_MIN; break;
			case Renderer::FUNC_MAX: return GL_MAX; break;
			default: LOG_ERROR << "Invalid render state value - expected blend operation value"; assert(false); return 0; break;
			}
		}

		unsigned int getGLCullMode(Renderer::RenderStateValue eCullMode)
		{
			switch (eCullMode)
			{
			case Renderer::CULL_BACK: return GL_BACK; break;
			case Renderer::CULL_FRONT: return GL_FRONT; break;
			case Renderer::CULL_FRONT_AND_BACK: return GL_FRONT_AND_BACK; break;
			default: LOG_ERROR << "Invalid render state value - expected cull mode"; assert(false); return 0; break;
			}
		}
	}

	void Renderer::applyRenderState(RenderState eState, RenderStateValue eValue)
	{
		switch (eState)
		{
		case STATE_ALPHA_TEST:			
			assert(false); break;
		case STATE_ALPHA_TEST_FUNC:		
			assert(false); break;
		case STATE_ALPHA_TEST_REF:		
			assert(false); break;
		case STATE_BLEND:				
			enableGLState(GL_BLEND, eValue); break;
		case STATE_BLEND_SRC:			
			glBlendFunc(getGLBlendFactor(eValue), getGLBlendFactor(m_aeState[STATE_BLEND_DST])); break;
		case STATE_BLEND_DST:			
			glBlendFunc(getGLBlendFactor(m_aeState[STATE_BLEND_SRC]), getGLBlendFactor(eValue)); break;
		case STATE_BLEND_OP:
			glBlendEquation(getGLBlendOp(eValue)); break;
		case STATE_DEPTH_WRITE:			
			assert(false); break;
		case STATE_DEPTH_TEST:			
			enableGLState(GL_DEPTH_TEST, eValue); break;
		case STATE_DEPTH_FUNC:			
			assert(false); break;
		case STATE_DEPTH_CLEAR_VALUE:	
			assert(false); break;
		case STATE_CULL_MODE:
			if (eValue == CULL_NONE)
			{
				enableGLState(GL_CULL_FACE, FALSE);
			}
			else
			{
				enableGLState(GL_CULL_FACE, TRUE);
				glCullFace(getGLCullMode(eValue));
			}
			break;
		case STATE_DEPTH_BIAS:			
			assert(false); break;
		case STATE_MULTISAMPLE:			
			assert(false); break;
		case DEPTH_BIAS_NONE:
			assert(false); break;
		case DEPTH_BIAS_FILL:
			assert(false); break;
		case DEPTH_BIAS_LINE:
			assert(false); break;
		case DEPTH_BIAS_POINT:
			assert(false); break;
		}
	}

} }