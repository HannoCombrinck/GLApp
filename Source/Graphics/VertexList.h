#pragma once

#include <Math/Math.h>
#include <vector>
#include <Logging/Log.h>

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
			VertexAttribute(const std::string& _sName, int _iIndex, int _iNumElements, VertexAttributeType _eType, int _iOffset, bool _bNormalized = false)
				: sName(_sName)
				, iIndex(_iIndex)
				, iNumElements(_iNumElements)
				, uType(_eType)
				, iOffset(_iOffset)
				, bNormalized(_bNormalized) {}

			std::string sName;			//!< Vertex attribute name.
			int iIndex;					//!< Index of the vertex attribute (as defined in shader via layout qualifier.
			int iNumElements;			//!< The number of elements that make up the vertex attribute
			VertexAttributeType uType;	//!< The type of the attribute elements.
			int iOffset;				//!< Offset of the attribute in bytes.
			bool bNormalized;			//!< Is the attribute a normalized value (e.g. normal vectors are normalized, positions aren't)
		};

		/*! @brief Defines the vertex layout as a list of vertex attributes.
		 *
		 */
		class VertexLayout
		{
		public:
			//! Add a vertex attribute to the layout.
			void add(const VertexAttribute& va) { m_Attributes.push_back(va); }
			//! Get a reference to the vertex attribute list.
			const std::vector<VertexAttribute>& getAttributes() const { return m_Attributes; }

		private:
			std::vector<VertexAttribute> m_Attributes;  //!< The list of vertex list attributes that define the vertex attribute layout.
		};
 
		/*! @brief The VertexListInterface provides an interface to get everything required to create a vertex array object (VAO).
		 *
		 */
		class VertexListInterface
		{
		public:
			//! Constructor.
			VertexListInterface() {}
			//! Destructor.
			virtual ~VertexListInterface() {}

			//! Get a pointer to the vertex buffer data.
			virtual const void* getVertexBufferData() const = 0;
			//! Get the vertex buffer size in bytes.
			virtual unsigned int getVertexBufferSize() const = 0;
			//! Get the number of vertices.
			virtual unsigned int getNumVertices() const = 0;
			//! Get a pointer to the index buffer data.
			virtual const void* getIndexBufferData() const = 0;
			//! Get the index buffer size in bytes.
			virtual unsigned int getIndexBufferSize() const = 0;
			//! Get the number of indices.
			virtual unsigned int getNumIndices() const = 0;
			//! Get the vertex attribute layout.
			virtual boost::shared_ptr<VertexLayout> getVertexLayout() const = 0;
			//! Get vertex size in bytes.
			virtual int getVertexSize() const = 0;
		};

		/*! @brief VertexList has vertex data, index data and the vertex layout description.
		 *
		 */
		template<class VertexType>
		class VertexList : public VertexListInterface
		{
		public:
			VertexList(const boost::shared_ptr<VertexLayout>& spVertexLayout)
				: m_spVertexLayout(spVertexLayout)
			{ 
				LOG_VERBOSE << "VertexList constructor";
				assert(m_spVertexLayout);
			}

			virtual ~VertexList() 
			{ 
				LOG_VERBOSE << "VertexList destructor"; 
			}

			virtual const void* getVertexBufferData() const { return reinterpret_cast<const void*>(&m_aVertices[0]); }
			virtual unsigned int getVertexBufferSize() const { return m_aVertices.size() * sizeof(VertexType); }
			virtual unsigned int getNumVertices() const { return m_aVertices.size(); }
			virtual const void* getIndexBufferData() const { return reinterpret_cast<const void*>(&m_aVertices[0]); }
			virtual unsigned int getIndexBufferSize() const { return m_aIndices.size() * sizeof(unsigned int); }
			virtual unsigned int getNumIndices() const { return m_aIndices.size(); }
			virtual boost::shared_ptr<VertexLayout> getVertexLayout() const { return m_spVertexLayout; }
			virtual int getVertexSize() const { return sizeof(VertexType); }

			//! Add a vertex to the list.
			void addVertex(VertexType vertex) { m_aVertices.push_back(vertex); }
			//! Add an index to the list.
			void addIndex(unsigned int uIndex) { m_aIndices.push_back(uIndex); }

			//! Modify the vertex data.
			std::vector<VertexType>& modifyVertices() { return m_aVertices;}
			//! Get the vertex data.
			const std::vector<VertexType>& getVertices() const { return m_aVertices; }
			
			//! Modify the index data.
			std::vector<unsigned int>& modifyIndices() { return m_aIndices; }
			//! Get the index data.
			const std::vector<unsigned int>& getIndices() const { return m_aIndices; }

		private:
			boost::shared_ptr<VertexLayout> m_spVertexLayout;	//!< The vertex layout description.
			std::vector<VertexType> m_aVertices;				//!< The vertex data.
			std::vector<unsigned int> m_aIndices;				//!< The index data.
		};
	}
}
