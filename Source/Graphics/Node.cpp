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
	
	void Node::addChild(const boost::shared_ptr<Spatial>& spSpatial)
	{
		assert(spSpatial);
		m_aChildren.push_back(spSpatial);
	}

	void Node::removeChild(const boost::shared_ptr<Spatial>& spSpatial)
	{
		assert(spSpatial);
		m_aChildren.erase(boost::remove(m_aChildren, spSpatial), m_aChildren.end());
	}

	void Node::removeAllChildren()
	{
		m_aChildren.clear();
	}

	void Node::apply(const boost::function<void(const boost::shared_ptr<Spatial>&)>& f)
	{
		Spatial::apply(f);
		boost::for_each(m_aChildren, [this, &f](const boost::shared_ptr<Spatial>& spSpatial) {
			spSpatial->apply(f);
		});
	}

	void Node::onUpdate(const Mat4& mParent)
	{
		boost::for_each(m_aChildren, [&mParent](const boost::shared_ptr<Spatial>& spSpatial) {
			spSpatial->update(mParent);
		});
	}

} }