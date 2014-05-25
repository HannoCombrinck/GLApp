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
			//! Constructor.
			Geometry();
			//! Destructor.
			~Geometry();
		
			//! Set the vertex list.
			void setVertexList(const boost::shared_ptr<VertexList>& spVertexList) { m_spVertexList = spVertexList; }
			//! Getter for setVertexList().
			boost::shared_ptr<VertexList> getVertexList() const { return m_spVertexList; }

			//! Set the geometry buffer ID.
			void setBufferID(unsigned int uID) { m_uID = uID; }
			//! Getter for setBufferID().
			unsigned int getBufferID() const { return m_uID; }

		private:
			boost::shared_ptr<VertexList> m_spVertexList; //!< The original vertex list from which the buffer was created.
			unsigned int m_uID;							  //!< The geometry buffer ID - i.e. OpenGL Vertex Array Object (VAO).

		};
	}
}