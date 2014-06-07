#include "Renderer.h"

#include <GL/glew.h>
#include <Logging/Log.h>
#include <Graphics/Geometry.h>
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
		//////////////////////////////////////////////////////////////////////////
		// Temp settings for testing - these will be encapsulated elsewhere
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glEnable(GL_DEPTH_TEST);
		glShadeModel(GL_SMOOTH);
		glDisable(GL_CULL_FACE);
		glDisable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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


	boost::shared_ptr<Geometry> Renderer::createGeometry(const boost::shared_ptr<VertexList>& spVertexList)
	{
		LOG_DEBUG << "Creating geometry hardware buffers...";
		// Create VAO
		unsigned int uVAO = ~0;
		glGenVertexArrays(1, &uVAO);
		glBindVertexArray(uVAO);

		// Create VBO
		unsigned int uVBO = ~0;
		glGenBuffers(1, &uVBO);
		glBindBuffer(GL_ARRAY_BUFFER, uVBO);
		glBufferData(GL_ARRAY_BUFFER, spVertexList->getVertexData().size()*sizeof(Vertex), &spVertexList->getVertexData()[0], GL_STATIC_DRAW);

		// connect the xyz to the "vert" attribute of the vertex shader
		//glVertexAttribPointer(/*index*/0, /*num members i.e. 3 floats for position*/ 3, /*type of elements*/ GL_FLOAT, /*normalized*/ GL_FALSE, /*stride i.e. size of entire vertex struct*/ sizeof(Vertex), /*position data*/ NULL);
		//glEnableVertexAttribArray(/*index*/ 0);

		// connect the uv coords to the "vertTexCoord" attribute of the vertex shader
		//glEnableVertexAttribArray(gWoodenCrate.shaders->attrib("vertTexCoord"));
		//glVertexAttribPointer(gWoodenCrate.shaders->attrib("vertTexCoord"), 2, GL_FLOAT, GL_TRUE,  5*sizeof(GLfloat), (const GLvoid*)(3 * sizeof(GLfloat)));

		unsigned int uIB = ~0;
		glGenBuffers(1, &uIB);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uIB);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, spVertexList->getIndexData().size()*sizeof(unsigned int), &spVertexList->getIndexData()[0], GL_STATIC_DRAW);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		LOG_DEBUG << "Successfully created geometry hardware buffers.";
		return boost::shared_ptr<Geometry>(new Geometry(uVAO, uVBO, uIB));
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

	void Renderer::applyRenderState(unsigned int uState, unsigned int uValue)
	{
		switch (uState)
		{
		case STATE_ALPHA_TEST: 
			assert(false);
			break;
		case STATE_ALPHA_TEST_FUNC: 
			assert(false);
			break;
		case STATE_ALPHA_TEST_REF: 
			assert(false);
			break;
		case STATE_BLEND: 
			if (uValue == TRUE)
				glEnable(GL_BLEND);
			else if (uValue == FALSE)
				glDisable(GL_BLEND);
			else
			{
				LOG_ERROR << "Invalid render state value";
				assert(false);
			}
			break;
		case STATE_BLEND_SRC:
			assert(false);
			break;
		case STATE_BLEND_DST: 
			assert(false);
			break;
		case STATE_BLEND_FUNC: 
			assert(false);
			break;
		case STATE_DEPTH_WRITE: 
			assert(false);
			break;
		case STATE_DEPTH_TEST: 
			assert(false);
			break;
		case STATE_DEPTH_FUNC: 
			assert(false);
			break;
		case STATE_DEPTH_CLEAR_VALUE: 
			assert(false);
			break;
		case STATE_CULL: 
			if (uValue == TRUE)
				glEnable(GL_CULL_FACE);
			else if (uValue == FALSE)
				glDisable(GL_CULL_FACE);
			else
			{
				LOG_ERROR << "Invalid render state value";
				assert(false);
			}
			break;
		case STATE_CULL_MODE: 
			assert(false);
			break;
		case STATE_DEPTH_BIAS: 
			assert(false);
			break;
		case STATE_MULTISAMPLE: 
			assert(false);
			break;
		}
	}

} }