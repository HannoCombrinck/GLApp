#include "Renderer.h"

#include <GL/glew.h>
#include <Logging/Log.h>
#include <Graphics/VertexList.h>

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
		memset(m_auState, 0, sizeof(unsigned int)*STATE_COUNT);

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

	//namespace
	//{
	//	unsigned int getGLType(unsigned int uType)
	//	{
	//		switch (uType)
	//		{
	//			case: TYPE_FLOAT: return GL_FLOAT; break;
	//			case: TYPE_INT: return GL_INT; break;
	//			case: TYPE_BOOL: return GL_BOOL; break;
	//		}
	//	}
	//}

//	boost::shared_ptr<Geometry> Renderer::createGeometry(const boost::shared_ptr<VertexList>& spVertexList)
//	{
//		LOG_DEBUG << "Creating geometry hardware buffers...";
//		// Create VAO
//		unsigned int uVAO = ~0;
//		glGenVertexArrays(1, &uVAO);
//		glBindVertexArray(uVAO);
//
//		// Create VBO
//		unsigned int uVBO = ~0;
//		glGenBuffers(1, &uVBO);
//		glBindBuffer(GL_ARRAY_BUFFER, uVBO);
//		glBufferData(GL_ARRAY_BUFFER, spVertexList->getVertexData().size()*sizeof(Vertex), &spVertexList->getVertexData()[0], GL_STATIC_DRAW);
//
//		// connect the xyz to the "vert" attribute of the vertex shader
//		//glVertexAttribPointer(/*index*/0, /*num members i.e. 3 floats for position*/ 3, /*type of elements*/ GL_FLOAT, /*normalized*/ GL_FALSE, /*stride i.e. size of entire vertex struct*/ sizeof(Vertex), /*position data*/ NULL);
//		//glEnableVertexAttribArray(/*index*/ 0);
//
//		// connect the uv coords to the "vertTexCoord" attribute of the vertex shader
//		//glEnableVertexAttribArray(gWoodenCrate.shaders->attrib("vertTexCoord"));
//		//glVertexAttribPointer(gWoodenCrate.shaders->attrib("vertTexCoord"), 2, GL_FLOAT, GL_TRUE,  5*sizeof(GLfloat), (const GLvoid*)(3 * sizeof(GLfloat)));
//
//		unsigned int uIB = ~0;
//		glGenBuffers(1, &uIB);
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uIB);
//		glBufferData(GL_ELEMENT_ARRAY_BUFFER, spVertexList->getIndexData().size()*sizeof(unsigned int), &spVertexList->getIndexData()[0], GL_STATIC_DRAW);
//
//		glBindVertexArray(0);
//		glBindBuffer(GL_ARRAY_BUFFER, 0);
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//
//		LOG_DEBUG << "Successfully created geometry hardware buffers.";
//		return boost::shared_ptr<Geometry>(new Geometry(uVAO, uVBO, uIB));
//	}

	void Renderer::clear()
	{
		clear(COLOUR_BUFFER | DEPTH_BUFFER | ACCUMULATION_BUFFER | STENCIL_BUFFER);
	}

	void Renderer::clear(unsigned int uMask)
	{
		unsigned int uGLMask = 0;
		uGLMask |= (uMask & COLOUR_BUFFER) ? GL_COLOR_BUFFER_BIT : 0;
		uGLMask |= (uMask & DEPTH_BUFFER) ? GL_DEPTH_BUFFER_BIT : 0;
		uGLMask |= (uMask & ACCUMULATION_BUFFER) ? GL_ACCUM_BUFFER_BIT : 0;
		uGLMask |= (uMask & STENCIL_BUFFER) ? GL_STENCIL_BUFFER_BIT : 0;

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

	void Renderer::setRenderState(unsigned int uState, unsigned int uValue)
	{
		assert(uState < STATE_COUNT);

		if (m_auState[uState] == uValue)
		{
			LOG_VERBOSE << "Ignoring redundant state change";
			return;
		}

		applyRenderState(uState, uValue);
	}

	namespace
	{
		void enableGLState(unsigned int uState, unsigned int uBool)
		{
			switch (uBool)
			{
			case Renderer::TRUE: glEnable(uState); break;
			case Renderer::FALSE: glDisable(uState); break;
			default: LOG_ERROR << "Invalid render state value - expected TRUE or FALSE."; assert(false); break;
			}
		}

		unsigned int getGLBlendFactor(unsigned int uBlendFactor)
		{
			switch (uBlendFactor)
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
			default: LOG_ERROR << "Invalid render state value - expected blend factor value."; assert(false); return 0; break;
			}
		}

		unsigned int getGLBlendOp(unsigned int uBlendOp)
		{
			switch (uBlendOp)
			{
			case Renderer::FUNC_ADD: return GL_FUNC_ADD; break;
			case Renderer::FUNC_SUBTRACT: return GL_FUNC_SUBTRACT; break;
			case Renderer::FUNC_REVERSE_SUBTRACT: return GL_FUNC_REVERSE_SUBTRACT; break;
			case Renderer::FUNC_MIN: return GL_MIN; break;
			case Renderer::FUNC_MAX: return GL_MAX; break;
			default: LOG_ERROR << "Invalid render state value - expected blend operation value."; assert(false); return 0; break;
			}
		}

		unsigned int getGLCullMode(unsigned int uCullMode)
		{
			switch (uCullMode)
			{
			case Renderer::CULL_BACK: return GL_BACK; break;
			case Renderer::CULL_FRONT: return GL_FRONT; break;
			case Renderer::CULL_FRONT_AND_BACK: return GL_FRONT_AND_BACK; break;
			default: LOG_ERROR << "Invalid render state value - expected cull mode."; assert(false); return 0; break;
			}
		}
	}

	void Renderer::applyRenderState(unsigned int uState, unsigned int uValue)
	{
		switch (uState)
		{
		case STATE_ALPHA_TEST:			
			assert(false); break;
		case STATE_ALPHA_TEST_FUNC:		
			assert(false); break;
		case STATE_ALPHA_TEST_REF:		
			assert(false); break;
		case STATE_BLEND:				
			enableGLState(GL_BLEND, uValue); break;
		case STATE_BLEND_SRC:			
			glBlendFunc(getGLBlendFactor(uValue), m_auState[STATE_BLEND_DST]); break;
		case STATE_BLEND_DST:			
			glBlendFunc(m_auState[STATE_BLEND_SRC], getGLBlendFactor(uValue)); break;
		case STATE_BLEND_OP:
			glBlendEquation(getGLBlendOp(uValue)); break;
		case STATE_DEPTH_WRITE:			
			assert(false); break;
		case STATE_DEPTH_TEST:			
			enableGLState(GL_DEPTH, uValue); break;
		case STATE_DEPTH_FUNC:			
			assert(false); break;
		case STATE_DEPTH_CLEAR_VALUE:	
			assert(false); break;
		case STATE_CULL_MODE:
			if (uValue == CULL_NONE)
			{
				enableGLState(GL_CULL_FACE, FALSE);
			}
			else
			{
				enableGLState(GL_CULL_FACE, TRUE);
				glCullFace(getGLCullMode(uValue));
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