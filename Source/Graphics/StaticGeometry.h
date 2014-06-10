#pragma once

#include <Graphics/Geometry.h>

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
			friend class Renderer;

			//! Destructor.
			~StaticGeometry();
		
			//! Get the vertex buffer i.e. VBO.
			unsigned int getVBO() const { return m_uVBO; }
			//! Get the index buffer.
			unsigned int getIB() const { return m_uIB; }

		protected:
			//! Protected constructor - must be created by Renderer.
			StaticGeometry(unsigned int uVAO, unsigned int uVBO, unsigned int uIB);

		private:
			unsigned int m_uVBO; //!< The geometry VBO - Vertex buffer object
			unsigned int m_uIB;	 //!< The geometry index buffer.

		};
	}
}