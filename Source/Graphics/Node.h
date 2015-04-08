#pragma once

#include <Graphics/Spatial.h>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <vector>

namespace baselib 
{
	namespace graphics
	{
		class Visual;
	}
}

namespace baselib 
{
	namespace graphics
	{
		/*! @brief Defines a Spatial Node in a directed acyclic graph.
		 *
		 */
		class Node : public Spatial
		{
		public:
			//! Creates a Node.
			static boost::shared_ptr<Node> create();

			//! Destructor.
			virtual ~Node();

			//! Add a child node.
			void addChild(const boost::shared_ptr<Spatial>& spSpatial);
			//! Removes a child node.
			void removeChild(const boost::shared_ptr<Spatial>& spSpatial);
			//! Remove all children nodes.
			void removeAllChildren();

			//! Apply f to this node and all its children.
			virtual void traverse(const boost::function<void(const boost::shared_ptr<Spatial>&)>& f);

		protected:
			//! Protected constructor - must be created by static create().
			Node();

		private:
			//! Recursively update children Nodes.
			virtual void onUpdate(const Mat4& mParent);

			std::vector<boost::shared_ptr<Spatial>> m_aChildren; //!< List of children Nodes.
		};
	}
}