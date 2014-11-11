#pragma once

#include <Graphics/Geometry.h>

namespace baselib 
{
	namespace graphics
	{
		class VertexListInterface;
	}
}

namespace baselib 
{
	namespace graphics
	{
		/*! @brief Contains the hardware buffers for a static piece of geometry (i.e. Geometry that is created once and doesn't change).
		 *
		 */
		class StaticGeometry : public Geometry
		{
		public:
			//! Creates and returns a static geometry from a vertex list.
			static boost::shared_ptr<StaticGeometry> create(const boost::shared_ptr<VertexListInterface>& spVertexList, PrimitiveType ePrimitiveType);

			//! Destructor.
			virtual ~StaticGeometry();
		
			//! Get the vertex buffer i.e. VBO.
			unsigned int getVBO() const { return m_uVBO; }
			//! Get the index buffer.
			unsigned int getIB() const { return m_uIB; }

		protected:
			//! Protected constructor - must be created by static create().
			StaticGeometry(unsigned int uVAO, unsigned int uVBO, unsigned int uIB, PrimitiveType ePrimitiveType, const boost::shared_ptr<VertexListInterface>& spVertexList);

		private:
			unsigned int m_uVBO; //!< The geometry VBO - Vertex buffer object
			unsigned int m_uIB;	 //!< The geometry index buffer.

		};
	}
}