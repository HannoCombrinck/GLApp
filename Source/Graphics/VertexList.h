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
				, eType(_eType)
				, iOffset(_iOffset)
				, bNormalized(_bNormalized) {}

			static unsigned int SizeOfType(VertexAttributeType _eType)
			{
				switch (_eType)
				{
					case TYPE_FLOAT : return sizeof(float); break;
					case TYPE_INT : return sizeof(int);	break;
					case TYPE_BOOL : return sizeof(bool); break; // TODO: Check if sizeof(bool) is correct size
					default: LOG_ERROR << __FUNCTION__": Invalid vertex attribute type"; assert(false); return 0; break;
				}
			}

			std::string sName;			//!< Vertex attribute name.
			int iIndex;					//!< Index of the vertex attribute (as defined in shader via layout qualifier.
			int iNumElements;			//!< The number of elements that make up the vertex attribute
			VertexAttributeType eType;	//!< The type of the attribute elements.
			int iOffset;				//!< Offset of the attribute in bytes.
			bool bNormalized;			//!< Is the attribute a normalized value (e.g. normal vectors are normalized, positions aren't)
		};

		/*! @brief Defines the vertex layout as a list of vertex attributes.
		 *
		 */
		class VertexLayout
		{
		public:
			//! Creates a VertexLayout.
			static boost::shared_ptr<VertexLayout> create() { return boost::shared_ptr<VertexLayout>(new VertexLayout()); }

			//! Add a vertex attribute to the layout.
			void add(const VertexAttribute& va) { m_Attributes.push_back(va); }
			//! Add a vertex attribute to the layout using the current attribute offset and increment automatically.
			void add(const std::string& _sName, int _iNumElements, VertexAttributeType _eType, bool _bNormalized = false)
			{
				m_Attributes.push_back( VertexAttribute(_sName, m_iPrevAttributeIndex, _iNumElements, _eType, m_iPrevAttributeOffset, _bNormalized) );
				m_iPrevAttributeOffset += _iNumElements * VertexAttribute::SizeOfType(_eType);
				m_iPrevAttributeIndex++;
			}
			//! Get a reference to the vertex attribute list.
			const std::vector<VertexAttribute>& getAttributes() const { return m_Attributes; }

		protected:
			//! Protected constructor - must be created by static create().
			VertexLayout() : m_iPrevAttributeOffset(0), m_iPrevAttributeIndex(0) {}

		private:
			std::vector<VertexAttribute> m_Attributes;  //!< The list of vertex list attributes that define the vertex attribute layout.
			int m_iPrevAttributeOffset;
			int m_iPrevAttributeIndex;
		};
 
		/*! @brief The VertexListInterface provides an interface to get everything required to create a vertex array object (VAO).
		 *
		 */
		class VertexListInterface
		{
		public:
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
			virtual const void* getIndexBufferData() const { return reinterpret_cast<const void*>(&m_aIndices[0]); }
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
