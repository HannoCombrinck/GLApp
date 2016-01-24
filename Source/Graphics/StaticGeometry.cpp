#include "StaticGeometry.h"

#include <GL/glew.h>
#include <Logging/Log.h>
#include <Graphics/VertexList.h>

#include <boost/range/algorithm/for_each.hpp>

namespace baselib { namespace graphics {
	
	namespace
	{
		GLenum getGLType(VertexAttributeType eType)
		{
			switch (eType)
			{
			case TYPE_FLOAT: return GL_FLOAT; break;
			case TYPE_INT: return GL_INT; break;
			case TYPE_BOOL: return GL_BOOL; break;
			default: LOG_ERROR << "Invalid vertex attribute type."; assert(false); return 0; break;
			}
		}

		GLboolean getGLBool(bool bValue)
		{
			if (bValue) 
				return GL_TRUE;
			return GL_FALSE;
		}
	}

	std::shared_ptr<StaticGeometry> StaticGeometry::create(const std::shared_ptr<VertexListInterface>& spVertexList, PrimitiveType ePrimitiveType)
	{
		LOG_VERBOSE << "Creating static geometry hardware buffers";
		
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
		const auto& aAttributes = spVertexLayout->getAttributes();
		boost::for_each(aAttributes, [iVertexSize](const VertexAttribute& va) {
			glVertexAttribPointer(va.iIndex, va.iNumElements, getGLType(va.eType), getGLBool(va.bNormalized), iVertexSize, (const GLvoid*)va.iOffset);
			glEnableVertexAttribArray(va.iIndex);
		});

		// Create index buffer
		unsigned int uIB = ~0;
		glGenBuffers(1, &uIB);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uIB);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, spVertexList->getIndexBufferSize(), spVertexList->getIndexBufferData(), GL_STATIC_DRAW);

		// Unbind VAO
		glBindVertexArray(0);

		LOG_VERBOSE << "Successfully created static geometry hardware buffers";
		return std::shared_ptr<StaticGeometry>(new StaticGeometry(uVAO, uVBO, uIB, ePrimitiveType, spVertexList));
	}

	StaticGeometry::StaticGeometry(unsigned int uVAO, unsigned int uVBO, unsigned int uIB, PrimitiveType ePrimitiveType, const std::shared_ptr<VertexListInterface>& spVertexList)
		: Geometry(uVAO, ePrimitiveType, spVertexList)
		, m_uVBO(uVBO)
		, m_uIB(uIB)
	{
		LOG_VERBOSE << "StaticGeometry constructor";
	}

	StaticGeometry::~StaticGeometry()
	{
		LOG_VERBOSE << "StaticGeometry destructor";
		glDeleteBuffers(1, &m_uVBO);
		glDeleteBuffers(1, &m_uIB);
	}

} }