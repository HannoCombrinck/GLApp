#pragma once

namespace baselib 
{
	namespace graphics
	{
		class Geometry
		{
		public:
			//! Destructor.
			~Geometry();
		
			//! Get the VAO.
			unsigned int getVAO() const { return m_uVAO; }
			//! Get the vertex buffer i.e. VBO.
			unsigned int getVBO() const { return m_uVBO; }
			//! Get the index buffer.
			unsigned int getIB() const { return m_uIB; }

		private:
			friend class Renderer;
			//! Private constructor - must be created by Renderer.
			Geometry(unsigned int uVAO, unsigned int uVBO, unsigned int uIB);

			unsigned int m_uVAO;						  //!< The geometry VAO - Vertex array object.

			// VBO and IB should move down to implementations - Geometry should maintain VAO level state only.
			unsigned int m_uVBO;						  //!< The geometry VBO - Vertex buffer object
			unsigned int m_uIB;							  //!< The geometry index buffer.

		};
	}
}