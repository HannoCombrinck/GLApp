#pragma once

#include <Graphics/Spatial.h>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <vector>

namespace baselib 
{
	namespace graphics
	{
		class Node : public Spatial
		{
		public:
			//! Constructor
			Node();
			//! Destructor
			~Node();

		private:
			std::vector<boost::shared_ptr<Node>> m_aChildren; //!< List of children Nodes.
			boost::weak_ptr<Node> m_wpParent;				  //!< Weak reference to parent Node.

		};
	}
}