#pragma once

#include <Math/Math.h>
#include <vector>

#include <Logging/Log.h>

using namespace std;

namespace baselib
{
	namespace graphics
	{
		enum VertexAttributeType
		{
			TYPE_FLOAT,
			TYPE_INT,
			TYPE_BOOL,
		};

		/*! @brief Defines a single vertex attribute.
		 *
		 *  A VertexAttribute's index and type should match up with vertex attributes in shaders.
		 */
		struct VertexAttribute 
		{
			//! Constructor.
			VertexAttribute(const string& _sName, int _iAttribIndex, int _iNumElements, unsigned int _uType)
				: sName(_sName)
				, iAttribIndex(_iAttribIndex)
				, iNumElements(_iNumElements)
				, uType(_uType) {}

			string sName;		//!< Vertex attribute name.
			int iAttribIndex;	//!< Index of the vertex attribute (as defined in shader via layout qualifier.
			int iNumElements;	//!< The number of elements that make up the vertex attribute.s
			unsigned int uType;	//!< The type of the attribute elements.
		};

		/*! @brief Defines a vertex layout as a list of vertex attributes.
		 *
		 */
		class VertexLayout
		{
		public:
			//! Add a vertex attribute to the layout.
			void add(const VertexAttribute& va) { m_Attributes.push_back(va); }
			//! Get a reference to the vertex attribute list.
			const vector<VertexAttribute>& getAttributes() const { return m_Attributes; }

		private:
			vector<VertexAttribute> m_Attributes;  //!< The list of vertex list attributes that define the vertex layout.
		};
 
		/*! @brief A VertexList holds vertex data, index data and the vertex layout description.
		 *
		 *  Geometry buffers are created from VertexLists.
		 */
		template <class VertexType>
		class VertexList
		{
		public:
			//! Constructor.
			VertexList() { LOG_VERBOSE << "VertexList constructor";	}
			//! Destructor.
			~VertexList() { LOG_VERBOSE << "VertexList destructor"; }

			//! Set the vertex layout.
			void setVertexLayout(const boost::shared_ptr<VertexLayout>& spVertexLayout) { m_spVertexLayout = spVertexLayout; }
			//! Get the vertex layout.
			boost::shared_ptr<VertexLayout> getVertexLayout() const { return m_spVertexLayout; }

			//! Clear all vertices and indices.
			void clear() 
			{ 
				m_aVertices.clear(); 
				m_aIndices.clear(); 
			}

			//! Add a vertex to the list.
			void addVertex(VertexType vertex) { m_aVertices.push_back(vertex); }
			//! Add an index to the list.
			void addIndex(unsigned int uIndex) { m_aIndices.push_back(uIndex); }

			//! Modify the vertex data.
			vector<VertexType>& modifyVertexData() { return m_aVertices;}
			//! Get the vertex data.
			const vector<VertexType>& getVertexData() const { return m_aVertices; }

			//! Modify the index data.
			vector<unsigned int>& modifyIndexData() { return m_aIndices; }
			//! Get the index data.
			const vector<unsigned int>& getIndexData() const { return m_aIndices; }
	
		private:
			boost::shared_ptr<VertexLayout> m_spVertexLayout;	//!< The vertex layout description.
			vector<VertexType> m_aVertices;						//!< The vertex data.
			vector<unsigned int> m_aIndices;					//!< The index data.
		};
	}
}
