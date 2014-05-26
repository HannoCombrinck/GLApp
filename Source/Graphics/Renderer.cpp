#include "Renderer.h"

#include <GL/glew.h>
#include <Logging/Log.h>
#include <Graphics/Geometry.h>
#include <Graphics/VertexList.h>

namespace baselib { namespace graphics {

	Renderer::Renderer()
	{
		LOG_VERBOSE << "Renderer constructor";
	}

	Renderer::~Renderer()
	{
		LOG_VERBOSE << "Renderer destructor";
	}

	void Renderer::init()
	{
		if (!glewInit())
		{
			LOG_ERROR << "Failed to initialize GLEW.";
			assert(false);
		}

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
		//glEnableVertexAttribArray(gWoodenCrate.shaders->attrib("vert"));
		//glVertexAttribPointer(gWoodenCrate.shaders->attrib("vert"), 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), NULL);

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

} }