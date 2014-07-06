#include "RenderJob.h"

#include <Logging/Log.h>
#include <Helpers/NullPtr.h>
#include <Graphics/VisualCollector.h>
#include <Graphics/Visual.h>
#include <Graphics/FrameBuffer.h>
#include <Graphics/VertexList.h>
#include <Graphics/Renderer.h>
#include <Graphics/Material.h>
#include <boost/range/algorithm/for_each.hpp>

namespace baselib { namespace graphics {

	boost::shared_ptr<RenderJob> RenderJob::create(const boost::shared_ptr<Renderer>& spRenderer)
	{
		return boost::shared_ptr<RenderJob>(new RenderJob(spRenderer));
	}

	RenderJob::RenderJob(const boost::shared_ptr<Renderer>& spRenderer)
		: m_spRenderer(spRenderer)
	{
		LOG_VERBOSE << "RenderJob constructor";
	}

	RenderJob::~RenderJob()
	{
		LOG_VERBOSE << "RenderJob destructor";
	}

	void RenderJob::execute(const boost::shared_ptr<Node>& spNode, 
						    const boost::shared_ptr<VisualCollector>& spVisualCollector, 
							const boost::shared_ptr<FrameBuffer>& spFrameBuffer, 
							const boost::shared_ptr<Camera>& spCamera)
	{
		// Collect and sort visible visuals
		spVisualCollector->collect(spNode);
		const auto& apVisuals = spVisualCollector->getVisuals();

		// Bind FrameBuffer
		spFrameBuffer->bind();

		// TODO: Check if frame buffer should be cleared
		m_spRenderer->clear();

		// Render visible, sorted list of visuals
		boost::shared_ptr<Geometry> spGeometry = null_ptr;
		boost::for_each(apVisuals, [this, &spGeometry](const Visual* pVisual) {
			pVisual->getMaterial()->bind();
			spGeometry = pVisual->getGeometry();
			spGeometry->bind();
			m_spRenderer->drawIndexed(spGeometry->getPrimitiveType(), spGeometry->getVertexList()->getNumIndices(), 0);
			spGeometry->unbind();
		});
	}

} }