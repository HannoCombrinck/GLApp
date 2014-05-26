#pragma once

#include <boost/shared_ptr.hpp>

namespace baselib 
{
	namespace graphics
	{
		class VertexList;
	}
}

namespace baselib 
{
	namespace graphics
	{
		/*!
		 *  Geometry assumes the existence of certain vertex attributes in shader during creation.
		 *  Default implementation just for static geometry i.e. buffer created once and never changes.
		 */
		class Geometry
		{
		public:
			//! Default Constructor.
			Geometry();
			//! Constructor with initial VAO, VBO and IB
			Geometry(unsigned int uVAO, unsigned int uVBO, unsigned int uIB);
			//! Destructor.
			~Geometry();
		
			//! Set the vertex list.
			void setVertexList(const boost::shared_ptr<VertexList>& spVertexList) { m_spVertexList = spVertexList; }
			//! Getter for setVertexList().
			boost::shared_ptr<VertexList> getVertexList() const { return m_spVertexList; }

			//! Set the VAO.
			void setVAO(unsigned int uVAO) { m_uVAO = uVAO; }
			//! Get the VAO.
			unsigned int getVAO() const { return m_uVAO; }

			//! Set the vertex buffer i.e. VBO.
			void setVBO(unsigned int uVBO) { m_uVBO = uVBO; }
			//! Get the vertex buffer i.e. VBO.
			unsigned int getVBO() const { return m_uVBO; }

			//! Set the index buffer.
			void setIB(unsigned int uIB) { m_uIB = uIB; }
			//! Get the index buffer.
			unsigned int getIB() const { return m_uIB; }

		private:
			boost::shared_ptr<VertexList> m_spVertexList; //!< The vertex list from which the hardware buffers are created.
			unsigned int m_uVAO;						  //!< The geometry VAO - Vertex array object.
			unsigned int m_uVBO;						  //!< The geometry VBO - Vertex buffer object
			unsigned int m_uIB;							  //!< The geometry index buffer.

		};
	}
}