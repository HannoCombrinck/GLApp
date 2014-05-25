#pragma once

#include <Math/Math.h>
#include <vector>

using namespace std;

namespace baselib
{
	namespace graphics
	{
		//! Fixed 64 byte vertex structure
		#pragma pack(push,1)
		struct Vertex 
		{
			float x, y, z; // 0 
			float nx, ny, nz; // 12 
			float tx, ty, tz; // 24 
			float btx, bty, btz; // 36
			float u, v; // 48 
			float u2, v2; // 56 
		};
		#pragma pack(pop)
 
		class VertexList
		{
		public:
			//! Constructor.
			VertexList();
			//! Destructor.
			~VertexList();

			//! Clear all vertices and indices.
			void clear();
 
			//! Add a vertex to the list.
			void addVertex(Vertex vertex) { m_aVertices.push_back(vertex); }
			//! Add an index to the list.
			void addIndex(unsigned int uIndex) { m_aIndices.push_back(uIndex); }

			//! Get the vertex data.
			const vector<Vertex>& getVertexData() const { return m_aVertices; }
			//! Get the index data.
			const vector<unsigned int>& getIndexData() const { return m_aIndices; }
	
		private:
			vector<Vertex> m_aVertices;		 //!< The vertex data.
			vector<unsigned int> m_aIndices; //!< The index data.
		};
	}
}
