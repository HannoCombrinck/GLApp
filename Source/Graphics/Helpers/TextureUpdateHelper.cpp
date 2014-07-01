#include "TextureUpdateHelper.h"

#include <Logging/Log.h>
#include <Helpers/NullPtr.h>
#include <Graphics/Renderer.h>
#include <Graphics/Shader.h>
#include <Graphics/Texture.h>
#include <Graphics/StaticGeometry.h>
#include <Graphics/VertexList.h>
#include <Graphics/FrameBuffer.h>

namespace baselib { namespace graphics {

	boost::shared_ptr<TextureUpdateHelper> TextureUpdateHelper::create(const boost::shared_ptr<Renderer> spRenderer)
	{
		assert(spRenderer);
		return boost::shared_ptr<TextureUpdateHelper>(new TextureUpdateHelper(spRenderer));
	}

	TextureUpdateHelper::TextureUpdateHelper(const boost::shared_ptr<Renderer> spRenderer)
		: m_spRenderer(spRenderer)
	{
		LOG_VERBOSE << "TextureUpdateHelper constructor";
		init();
	}

	TextureUpdateHelper::~TextureUpdateHelper()
	{
		LOG_VERBOSE << "TextureUpdateHelper destructor";
	}

	void TextureUpdateHelper::updateRegion(const boost::shared_ptr<Texture> spInputTexture, const boost::shared_ptr<Texture> spTargetTexture, const boost::shared_ptr<Shader> spShader)
	{
		updateRegion(spInputTexture, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f), spTargetTexture, spShader);
	}

	void TextureUpdateHelper::updateRegion(const boost::shared_ptr<Texture> spInputTexture, const Vec2& vMinTo, const Vec2& vMaxTo, const boost::shared_ptr<Texture> spTargetTexture, const boost::shared_ptr<Shader> spShader)
	{
		updateRegion(Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f), spInputTexture, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f), spTargetTexture, spShader);
	}

	void TextureUpdateHelper::updateRegion(const Vec2& vMinFrom, const Vec2& vMaxFrom, const boost::shared_ptr<Texture> spInputTexture, const Vec2& vMinTo, const Vec2& vMaxTo, const boost::shared_ptr<Texture> spTargetTexture, const boost::shared_ptr<Shader> spShader)
	{
		// TODO:
		m_spFrameBuffer->bind();
		//m_spFrameBuffer->setAttachment(spTargetTexture);
		spShader->bind();
		// set vMin's and vMax's in spShader
		// set spInputTexture in spShader
		spInputTexture->bind();
		m_spQuadGeometry->bind();
		m_spRenderer->drawIndexed(m_spQuadGeometry->getPrimitiveType(), m_spQuadGeometry->getVertexList()->getNumIndices(), 0);
	}

	void TextureUpdateHelper::init()
	{
		// TODO:
		// Create frame buffer
		// Create quad geometry
	}

} }