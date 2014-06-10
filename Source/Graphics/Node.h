#pragma once

#include <Graphics/Spatial.h>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <vector>

namespace baselib 
{
	namespace graphics
	{
		/*! @brief Defines a Spatial Node in a directed acyclic graph.
		 *
		 */
		class Node : public Spatial, public boost::enable_shared_from_this<Node>
		{
		public:
			//! Constructor.
			Node();
			//! Destructor.
			~Node();

			//! Add a child node. The child node's parent reference is set to this node.
			void addChild(const boost::shared_ptr<Node>& spNode);
			//! Removes a child node. Parent reference is set to null.
			void removeChild(const boost::shared_ptr<Node>& spNode);
			//! Remove all children nodes.
			void removeAllChildren();
			//! Detach this node - i.e. remove this Node from its parent's children list.
			void detachFromParent();

			//! Set parent Node.
			void setParent(const boost::shared_ptr<Node>& spNode) { m_wpParent = spNode; }
			//! Get parent Node.
			boost::shared_ptr<Node> getParent() const { return m_wpParent.lock(); }

		private:
			//! Recursively update children Nodes.
			virtual void onUpdate(const Mat4& mParent);

			std::vector<boost::shared_ptr<Node>> m_aChildren; //!< List of children Nodes.
			boost::weak_ptr<Node> m_wpParent;				  //!< Weak reference to parent Node.
		};
	}
}