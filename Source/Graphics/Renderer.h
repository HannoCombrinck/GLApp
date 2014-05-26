#pragma once

#include <boost/shared_ptr.hpp>

namespace baselib 
{
	namespace graphics
	{
		class Geometry;
		class VertexList;
	}
}

namespace baselib 
{
	namespace graphics
	{
		class Renderer
		{
		public:
			//! Constructor.
			Renderer();
			//! Destructor.
			~Renderer();
		
			//! Initialize renderer.
			void init();

			//! Create Geometry from a VertexList
			boost::shared_ptr<Geometry> createGeometry(const boost::shared_ptr<VertexList>& spVertexList);

		private:


		};
	}
}