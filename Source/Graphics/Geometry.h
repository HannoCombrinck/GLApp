#pragma once

#include <boost/shared_ptr.hpp>

namespace baselib 
{
	namespace graphics
	{
		class Geometry
		{
		public:
			//! Default Constructor.
			Geometry();
			//! Constructor with initial VAO, VBO and IB
			Geometry(unsigned int uVAO, unsigned int uVBO, unsigned int uIB);
			//! Destructor.
			~Geometry();
		
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
			unsigned int m_uVAO;						  //!< The geometry VAO - Vertex array object.
			// VBO and IB should move down to implementations - Geometry should maintain VAO level state only.
			unsigned int m_uVBO;						  //!< The geometry VBO - Vertex buffer object
			unsigned int m_uIB;							  //!< The geometry index buffer.

		};
	}
}