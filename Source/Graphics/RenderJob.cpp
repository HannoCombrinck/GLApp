#include "RenderJob.h"

#include <Logging/Log.h>
#include <Core/NullPtr.h>
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

	std::shared_ptr<RenderJob> RenderJob::create(const std::shared_ptr<Renderer>& spRenderer)
	{
		return std::shared_ptr<RenderJob>(new RenderJob(spRenderer));
	}

	RenderJob::RenderJob(const std::shared_ptr<Renderer>& spRenderer)
		: m_spRenderer(spRenderer)
	{
		LOG_VERBOSE << "RenderJob constructor";
	}

	RenderJob::~RenderJob()
	{
		LOG_VERBOSE << "RenderJob destructor";
	}

	void RenderJob::execute(const std::vector<Visual*>& apVisuals,
							const std::shared_ptr<FrameBuffer>& spFrameBuffer, 
							const std::shared_ptr<Camera>& spCamera,
							bool bClear/* = true*/)
	{
		execute(apVisuals, spFrameBuffer, spCamera, null_ptr, bClear);
	}

	void RenderJob::execute(const std::vector<Visual*>& apVisuals, 
							const std::shared_ptr<FrameBuffer>& spFrameBuffer, 
							const std::shared_ptr<Camera>& spCamera, 
							const std::shared_ptr<Shader>& spShader, 
							bool bClear /*= true*/)
	{
		// Setup FrameBuffer
		spFrameBuffer->bind();
		m_spRenderer->setViewportSize(Vec4(0, 0, spFrameBuffer->getWidth(), spFrameBuffer->getHeight()));
		if (bClear)
			m_spRenderer->clear();

		// Render visible, sorted list of visuals
		std::shared_ptr<Geometry> spGeometry = null_ptr;
		boost::for_each(apVisuals, [this, &spCamera, &spGeometry, &spShader](const Visual* pVisual) {

			auto spShaderLocal = spShader;
			if (!spShaderLocal)
				spShaderLocal = pVisual->getMaterial()->getShader();

			spShaderLocal->bind();
			spShaderLocal->setUniform("mProjection", spCamera->getProjectionMatrix());
			spShaderLocal->setUniform("mView", spCamera->getViewMatrix());
			spShaderLocal->setUniform("mWorld", pVisual->getWorldTransform());
			spShaderLocal->setUniform("sDiffuse", 0);

			if (auto spTexture = pVisual->getMaterial()->getTexture())
				spTexture->bind();

			spGeometry = pVisual->getGeometry();
			spGeometry->bind();

			m_spRenderer->drawIndexed(spGeometry->getPrimitiveType(), spGeometry->getVertexList()->getNumIndices(), 0);
		});
	}

} }