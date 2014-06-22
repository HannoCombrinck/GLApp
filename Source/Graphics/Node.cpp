#include "Node.h"

#include <Logging/Log.h>
#include <Graphics/Visual.h>
#include <boost/range/algorithm/for_each.hpp>
#include <boost/range/algorithm/remove.hpp>

namespace baselib { namespace graphics {

	Node::Node()
	{
		LOG_VERBOSE << "Node constructor";
	}

	Node::~Node()
	{
		LOG_VERBOSE << "Node destructor";
	}
	
	void Node::addChild(const boost::shared_ptr<Node>& spNode)
	{
		assert(spNode);
		assert(!spNode->getParent());
		m_aChildren.push_back(spNode);
		spNode->setParent(shared_from_this());
	}

	void Node::removeChild(const boost::shared_ptr<Node>& spNode)
	{
		assert(spNode);
		m_aChildren.erase(boost::remove(m_aChildren, spNode), m_aChildren.end());
	}

	void Node::removeAllChildren()
	{
		m_aChildren.clear();
	}

	void Node::detachFromParent()
	{
		if (auto spParent = m_wpParent.lock())
		{
			modifyLocal() = spParent->getWorld() * getLocal();
			spParent->removeChild(shared_from_this());
			setParent(boost::shared_ptr<Node>());
		}
	}

	void Node::onUpdate(const Mat4& mParent)
	{
		if (m_spVisual)
			m_spVisual->update(mParent);

		boost::for_each(m_aChildren, [&mParent](const boost::shared_ptr<Node>& spNode) {
			spNode->update(mParent);
		});
	}

} }