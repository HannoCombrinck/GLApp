#pragma once

#include <memory>

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
		/*! @brief Wrapper for hardware buffer that contains geometry information.
		 *
		 */
		class Geometry
		{
		public:
			//! Geometry primitive type.
			enum PrimitiveType
			{
				INVALID_PRIMITIVE = 0,

				POINTS, 
				LINE_STRIP, 
				LINE_LOOP, 
				LINES, 
				LINE_STRIP_ADJACENCY, 
				LINES_ADJACENCY, 
				TRIANGLE_STRIP, 
				TRIANGLE_FAN, 
				TRIANGLES, 
				TRIANGLE_STRIP_ADJACENCY, 
				TRIANGLES_ADJACENCY,
				PATCHES,

				PRIMITIVE_TYPE_COUNT
			};

			//! Destructor.
			virtual ~Geometry();
		
			//! Bind geometry buffer.
			void bind();
			//! Unbind geometry buffer.
			void unbind();

			//! Get the VAO.
			unsigned int getVAO() const { return m_uVAO; }
			//! Get the primitive type.
			PrimitiveType getPrimitiveType() const { return m_ePrimitiveType; }
			//! Get the vertex list.
			std::shared_ptr<VertexListInterface> getVertexList() const { return m_spVertexList; }

		protected:
			//! Protected constructor - derived classes must be created by static create.
			Geometry(unsigned int uVAO, PrimitiveType ePrimitiveType, const std::shared_ptr<VertexListInterface>& spVertexList);

		private:
			unsigned int m_uVAO;  //!< The geometry VAO - Vertex array object.
			PrimitiveType m_ePrimitiveType; //!< The type of primitive shapes the geometry is composed of.
			std::shared_ptr<VertexListInterface> m_spVertexList; //!< The vertex list used to create this goemetry buffer.

		};
	}
}