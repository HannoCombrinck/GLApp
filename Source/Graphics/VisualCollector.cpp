#include "VisualCollector.h"

#include <Logging/Log.h>
#include <Graphics/Node.h>
#include <Graphics/Visual.h>
#include <boost/range/algorithm/sort.hpp>

namespace baselib { namespace graphics {

	std::shared_ptr<VisualCollector> VisualCollector::create()
	{
		return std::shared_ptr<VisualCollector>(new VisualCollector());
	}

	VisualCollector::VisualCollector()
	{
		LOG_VERBOSE << "VisualCollector constructor";
	}

	VisualCollector::~VisualCollector()
	{
		LOG_VERBOSE << "VisualCollector destructor";
	}

	void VisualCollector::collect(const std::shared_ptr<Node>& spNode)
	{
		// Traverse Node hierarchy and selectively add visuals
		std::vector<Visual*>& apVisuals = m_apVisuals;
		spNode->traverse([&apVisuals](const std::shared_ptr<Spatial>& spSpatial) {
			if (auto spVisual = std::dynamic_pointer_cast<Visual>(spSpatial))
				apVisuals.push_back(spVisual.get()); // TODO: Only add visuals if they aren't culled/filtered
		});

		// Sort m_apVisuals
		//boost::sort(m_apVisuals, [](const Visual* pLHS, const Visual* pRHS) { return true; /*TODO: Write visual sorting predicate*/ });
	}

	void VisualCollector::clear()
	{
		m_apVisuals.clear();
	}

} }