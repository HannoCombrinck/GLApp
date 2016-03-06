#include "Node.h"

#include <Logging/Log.h>
#include <Graphics/Visual.h>
#include <boost/range/algorithm/for_each.hpp>
#include <boost/range/algorithm/remove.hpp>

namespace baselib { namespace graphics {

	std::shared_ptr<Node> Node::load(const fs::path& fsPath)
	{
		// Load node hierarchy from disk with ModelLoader
		return Node::create();
	}

	std::shared_ptr<Node> Node::create()
	{
		return std::shared_ptr<Node>(new Node());
	}

	Node::Node()
	{
		LOG_VERBOSE << "Node constructor";
	}

	Node::~Node()
	{
		LOG_VERBOSE << "Node destructor";
	}
	
	void Node::addChild(const std::shared_ptr<Spatial>& spSpatial)
	{
		assert(spSpatial);
		m_aChildren.push_back(spSpatial);
	}

	void Node::removeChild(const std::shared_ptr<Spatial>& spSpatial)
	{
		assert(spSpatial);
		m_aChildren.erase(boost::remove(m_aChildren, spSpatial), m_aChildren.end());
	}

	void Node::removeAllChildren()
	{
		m_aChildren.clear();
	}

	void Node::traverse(const boost::function<void(const std::shared_ptr<Spatial>&)>& f)
	{
		Spatial::traverse(f);
		boost::for_each(m_aChildren, [this, &f](const std::shared_ptr<Spatial>& spSpatial) {
			spSpatial->traverse(f);
		});
	}

	void Node::onUpdate(const Mat4& mParent)
	{
		boost::for_each(m_aChildren, [this, &mParent](const std::shared_ptr<Spatial>& spSpatial) {
			spSpatial->update(getWorldTransform());
		});
	}

} }