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

		protected:
			//! Protected constructor - derived classes must be created by Renderer.
			Geometry(unsigned int uVAO);

		private:
			unsigned int m_uVAO;  //!< The geometry VAO - Vertex array object.

		};
	}
}