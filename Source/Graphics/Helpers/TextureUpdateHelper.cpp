#include "TextureUpdateHelper.h"

#include <Logging/Log.h>
#include <Helpers/NullPtr.h>
#include <Graphics/RenderJob.h>
#include <Graphics/VisualCollector.h>
#include <Graphics/StaticGeometry.h>
#include <Graphics/FrameBuffer.h>

namespace baselib { namespace graphics {

	boost::shared_ptr<TextureUpdateHelper> TextureUpdateHelper::create(const boost::shared_ptr<Renderer> spRenderer)
	{
		return boost::shared_ptr<TextureUpdateHelper>(new TextureUpdateHelper(spRenderer));
	}

	TextureUpdateHelper::TextureUpdateHelper(const boost::shared_ptr<Renderer> spRenderer)
	{
		LOG_VERBOSE << "TextureUpdateHelper constructor";
		init(spRenderer);
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
		// TODO
	}

	void TextureUpdateHelper::init(const boost::shared_ptr<Renderer> spRenderer)
	{
		m_spRenderJob = RenderJob::create(spRenderer);
		m_spVisualCollector = VisualCollector::create();

		// TODO:
		// Create frame buffer
		// Create quad geometry
	}

} }