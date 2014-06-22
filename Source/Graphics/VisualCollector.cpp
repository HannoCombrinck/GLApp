#include "VisualCollector.h"

#include <Logging/Log.h>
#include <Graphics/Node.h>
#include <Graphics/Visual.h>
#include <boost/range/algorithm/sort.hpp>

namespace baselib { namespace graphics {

	VisualCollector::VisualCollector()
	{
		LOG_VERBOSE << "VisualCollector constructor";
	}

	VisualCollector::~VisualCollector()
	{
		LOG_VERBOSE << "VisualCollector destructor";
	}

	void VisualCollector::collect(const boost::shared_ptr<Node>& spNode)
	{
		m_apVisuals.clear();

		// Traverse Node hierarchy and selectively add visuals
		std::vector<Visual*>& apVisuals = m_apVisuals;
		spNode->forEach([&apVisuals](const boost::shared_ptr<Node>& spNode) {
			if (auto spVisual = spNode->getVisual()) 
				apVisuals.push_back(spVisual.get()); // TODO: Only add visuals if they aren't culled/filtered
		});

		// Sort m_apVisuals
		boost::sort(m_apVisuals, [](const Visual* pLHS, const Visual* pRHS) { return true; /*TODO: Write visual sorting predicate*/ });
	}

} }