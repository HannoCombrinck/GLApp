#include "RenderJob.h"

#include <Logging/Log.h>
#include <Helpers/NullPtr.h>
#include <Graphics/VisualCollector.h>
#include <Graphics/Visual.h>
#include <Graphics/FrameBuffer.h>
#include <Graphics/VertexList.h>
#include <Graphics/Renderer.h>
#include <Graphics/Material.h>
#include <Graphics/Shader.h>
#include <Graphics/Texture.h>
#include <Graphics/Camera.h>
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

		// Setup FrameBuffer
		spFrameBuffer->bind();
		m_spRenderer->setViewportSize(Vec4(0, 0, spFrameBuffer->getWidth(), spFrameBuffer->getHeight()));
		m_spRenderer->clear();

		// Render visible, sorted list of visuals
		boost::shared_ptr<Geometry> spGeometry = null_ptr;
		boost::for_each(apVisuals, [this, &spCamera, &spGeometry](const Visual* pVisual) {

			auto spShader = pVisual->getMaterial()->getShader();
			spShader->bind();
			spShader->setUniform(spShader->getUniform("mProjection"), spCamera->getProjectionMatrix());
			spShader->setUniform(spShader->getUniform("mView"), spCamera->getViewMatrix());
			spShader->setUniform(spShader->getUniform("mWorld"), pVisual->getWorldTransform());
			spShader->setUniform(spShader->getUniform("sDiffuse"), 0);

			if (auto spTexture = pVisual->getMaterial()->getTexture())
				spTexture->bind();

			spGeometry = pVisual->getGeometry();
			spGeometry->bind();

			m_spRenderer->drawIndexed(spGeometry->getPrimitiveType(), spGeometry->getVertexList()->getNumIndices(), 0);
		});
	}

} }