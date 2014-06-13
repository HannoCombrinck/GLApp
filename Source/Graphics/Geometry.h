#pragma once

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
			//! Destructor.
			virtual ~Geometry();
		
			//! Bind geometry buffer.
			void bind();
			//! Unbind geometry buffer.
			void unbind();

			//! Get the VAO.
			unsigned int getVAO() const { return m_uVAO; }

		protected:
			//! Protected constructor - derived classes must be created by Renderer.
			Geometry(unsigned int uVAO);

		private:
			unsigned int m_uVAO;  //!< The geometry VAO - Vertex array object.

		};
	}
}